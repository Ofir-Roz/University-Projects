#include "main_header.h"
extern int lineNum;

DataWord dataImage[MEMORY_SIZE];

CmdLine cmdImage[MEMORY_SIZE];

void identify_and_encrypt_data(int *pDC, char *string, bool *err_flag) {
    int tempInt;
    char tempChr;
    char wordBuff[WORD_BUFF_LEN], asciiBuff[ASCII_BUFF_LEN], lineBuff[MAX_LINE_LEN], *pLineBuff;
    pLineBuff = lineBuff;

    take_first_word_from_line(wordBuff, string);
    remove_word_from_string(string, wordBuff);
    strcpy(lineBuff, string);

    /* data handling */
    if (!strcmp(wordBuff, DATA)) {
        if (is_legal_data_args(string)) {
            /* take the digits one by one */
            while ((pLineBuff = take_next_integer(pLineBuff, &tempInt))) {
                /* make the digit suitable to the memory image */
                dataImage[(*pDC)++] = translate_integer_to_bin(tempInt);
            }
        }
        else {
            *err_flag = ON;
            print_err_or_warn("The data is invalid (non-digits, floats, etc...)", ERROR, lineNum);
            return;
        }
    }

    /* string handling */
    if (!strcmp(wordBuff, STRING)) {
        if (is_legal_string_args(string)) {
            extract_string_from_quotation_marks(asciiBuff, string);
            /* take the chars one by one */
            while ((tempChr = take_next_char(asciiBuff))) {
                /* make the ascii char suitable to the memory image */
                dataImage[(*pDC)++] = translate_ascii_to_bin(tempChr);
            }

            /* add the null terminator to the end of the sequence */
            dataImage[(*pDC)++] = translate_ascii_to_bin('\0');
        }
        else {
            *err_flag = ON;
            print_err_or_warn("The string is invalid (more then one parameter, etc...)", ERROR, lineNum);
            return;
        }
    }
}

DataWord translate_integer_to_bin(int integer) {
    MemWord word;
    word = initiate_memWord_to_zero();

    word.wordType.dataWord.data =(short) integer;
    return word.wordType.dataWord;
}

DataWord translate_ascii_to_bin(char chr) {
    MemWord word;
    word = initiate_memWord_to_zero();

    word.wordType.dataWord.data = (short)chr;
    return word.wordType.dataWord;
}

/*
 *
 *
 */

void build_first_cmd_word_and_more(int *pIC, char *line) {
    char wordBuff[WORD_BUFF_LEN],                                /* the name of the command */
    argsBuff[ARGS_BUFF_LEN];                                     /* the args part of the line */
    cmdOpCode cmdOpNum;                                          /* the number of the command */
    CmdWord cmdWord;                                             /* the binary command memWord */
    cmdWord = initiate_CmdWord_to_zero();

    take_first_word_from_line(wordBuff, line);
    cmdOpNum = get_cmd_op_code(wordBuff);
    take_args_of_cmd(argsBuff, line);

    /* get the memory memWord we want to put in the memory image */
    cmdWord.word.frsWord = get_cmd_frs_word(cmdOpNum, argsBuff);
    cmdImage[(*pIC)].memWord = cmdWord;
    cmdImage[(*pIC)].memWord.typeNum = frsWord;
    cmdImage[(*pIC)++].empty = OFF;

    take_args_of_cmd(argsBuff, line);
    /* continue to build additional words if needed to */
    if (is_more_words_to_build(cmdWord)) {
        build_addi_words_frs_pass(pIC, argsBuff, cmdWord);
    }
}

void build_addi_words_frs_pass(int *pIC, char *argsBuff, CmdWord cmdWord) {
    char soleArg[MAX_NAME_LEN], frsParArg[MAX_NAME_LEN], secParArg[MAX_NAME_LEN], /* the args parts of the line */
    originalArgs[MAX_LINE_LEN];                                                   /* only for the registers memWord */
    int regMetType;

    strcpy(originalArgs, argsBuff);

    while ((get_next_arg(argsBuff, soleArg)) && soleArg[0] != '\0' ) {

        switch (get_arg_type(soleArg)) {

            case IMMEDIATE_METHOD:
                cmdWord.word.addiWord = get_immediate_word(soleArg);
                cmdImage[(*pIC)].memWord = cmdWord;
                cmdImage[(*pIC)].memWord.typeNum = addiWord;
                cmdImage[(*pIC)++].empty = OFF;
                break;

            case DIRECT_METHOD:
                cmdImage[(*pIC)].memWord.typeNum = addiWord;
                cmdImage[(*pIC)++].empty = ON;
                break;

            case JMP_WITH_PARAM_METHOD:
                cmdImage[(*pIC)].memWord.typeNum = addiWord;
                cmdImage[(*pIC)++].empty = ON; /* for the memWord of the label before the args */
                take_next_arg_from_parentheses(soleArg, frsParArg);
                take_next_arg_from_parentheses(soleArg, secParArg);
                fill_addi_words_of_param_method(pIC, frsParArg, secParArg, cmdWord);
                break;

            case REGISTER_METHOD:
                regMetType = get_reg_met_type(originalArgs);
                fill_addi_words_of_reg_method(originalArgs, soleArg, regMetType, pIC, cmdWord);
                break;

            default:
                break;
        }
    }
}

void fill_addi_words_of_reg_method(char *argsBuff, char *soleArg, int regMetType, int *pIC, CmdWord cmdWord) {
    switch (regMetType) {

        case SRC_REGISTER_TYPE:
            (cmdWord).word.srcRegWord = get_src_reg_word(soleArg);
            cmdImage[(*pIC)].memWord = (cmdWord);
            cmdImage[(*pIC)].memWord.typeNum = srcWord;
            cmdImage[(*pIC)++].empty = OFF;
            break;

        case TAR_REGISTER_TYPE:
            (cmdWord).word.tarRegWord = get_tar_reg_word(soleArg);
            cmdImage[(*pIC)].memWord = (cmdWord);
            cmdImage[*pIC].memWord.typeNum = tarWord;
            cmdImage[(*pIC)++].empty = OFF;
            break;

        case COMB_REGISTER_TYPE:
            (cmdWord).word.combRegWord = get_comb_reg_word(argsBuff);
            cmdImage[(*pIC)].memWord = (cmdWord);      /* go back one spot on the memory */
            cmdImage[*pIC].memWord.typeNum = combWord;
            cmdImage[(*pIC)++].empty = OFF;
            break;

        default:
            break;
    }
}

int get_reg_met_type(char *argsBuff) {
    char srcWord[MAX_NAME_LEN], trgWord[MAX_NAME_LEN];
    char originalArgs[ARGS_BUFF_LEN];
    strcpy(originalArgs, argsBuff);

    if (!is_contains_one_word_only(argsBuff)) {

        take_two_words_sep_with_comma(srcWord, trgWord, argsBuff);
        strcpy(argsBuff, originalArgs);

        if (is_register(srcWord) && is_register(trgWord))
            return COMB_REGISTER_TYPE;
        else
            return SRC_REGISTER_TYPE;
    }
    else  /* only one memWord left on the argsBuff therefore it's must be target register */
        return TAR_REGISTER_TYPE;
}

void fill_addi_words_of_param_method(int *pIC, char *frsParArg, char *secParArg, CmdWord cmdWord) {
    int frsArgType, secArgType;

    frsArgType = get_arg_type(frsParArg);
    secArgType = get_arg_type(secParArg);

    /* first take care of the combined register addressing method */
    if (frsArgType == REGISTER_METHOD && secArgType == REGISTER_METHOD) {
        /* make the string compatible for the function */
        strcat(frsParArg, ", ");
        strcat(frsParArg, secParArg);

        (cmdWord).word.combRegWord = get_comb_reg_word(frsParArg);
        cmdImage[(*pIC)].memWord = cmdWord;
        cmdImage[(*pIC)].memWord.typeNum = combWord;
        cmdImage[(*pIC)++].empty = OFF;
        return;
    }

    /* taking care of the first argument inside the parentheses */
    switch (frsArgType) {
        case IMMEDIATE_METHOD:
            cmdWord.word.addiWord = get_immediate_word(frsParArg);
            cmdImage[(*pIC)].memWord = cmdWord;
            cmdImage[(*pIC)].memWord.typeNum = addiWord;
            cmdImage[(*pIC)++].empty = OFF;
            break;

        case DIRECT_METHOD:
            cmdImage[(*pIC)].memWord.typeNum = addiWord;
            cmdImage[(*pIC)++].empty = ON;
            break;

        case REGISTER_METHOD:
            (cmdWord).word.srcRegWord = get_src_reg_word(frsParArg);
            cmdImage[(*pIC)].memWord = (cmdWord);
            cmdImage[(*pIC)].memWord.typeNum = srcWord;
            cmdImage[(*pIC)++].empty = OFF;
            break;

        default:
            break;
    }

    /* taking care of the second argument inside the parentheses */
    switch (secArgType) {
        case IMMEDIATE_METHOD:
            cmdWord.word.addiWord = get_immediate_word(secParArg);
            cmdImage[(*pIC)].memWord = cmdWord;
            cmdImage[(*pIC)].memWord.typeNum = addiWord;
            cmdImage[(*pIC)++].empty = OFF;
            break;

        case DIRECT_METHOD:
            cmdImage[(*pIC)].memWord.typeNum = addiWord;
            cmdImage[(*pIC)++].empty = ON;
            break;

        case REGISTER_METHOD:
            (cmdWord).word.tarRegWord = get_tar_reg_word(secParArg);
            cmdImage[(*pIC)].memWord = (cmdWord);
            cmdImage[(*pIC)].memWord.typeNum = tarWord;
            cmdImage[(*pIC)++].empty = OFF;
            break;

        default:
            break;
    }
}

int get_arg_type(char *arg) {

    if (arg[0] == '#')
        return IMMEDIATE_METHOD;
    else
        if (isalpha(*arg) && is_label_syntax(arg) && !is_register(arg))
            return DIRECT_METHOD;
        else
            if (is_register(arg))
                return REGISTER_METHOD;
            else
                return JMP_WITH_PARAM_METHOD;
}

int get_command_num_of_addi_memWords(char *string) {
    char wordBuff[WORD_BUFF_LEN],       /* the name of the command */
    argsBuff[ARGS_BUFF_LEN];            /* the args part of the line */

    take_first_word_from_line(wordBuff, string);
    take_args_of_cmd(argsBuff, string);

    if ((get_cmd_op_code(wordBuff) == STOP) || (get_cmd_op_code(wordBuff) == RTS))
        /* no additional words needed */
        return 0;

    return get_num_of_addi_words_per_cmd(argsBuff);
}

void take_label_of_jmp_met(char *wholeJmpWord, char *label);

int get_num_of_addi_words_per_cmd(char *args) {
    char srcWord[MAX_NAME_LEN], trgWord[MAX_NAME_LEN], JmpWord[MAX_LINE_LEN],
    argsCpy[MAX_LINE_LEN], jmpLabel[MAX_NAME_LEN];
    int frsArgType, secArgType;
    strcpy(argsCpy, args);

    /* First find if there is more than one operand */
    if (!is_contains_one_word_only(args)) {
        take_two_words_sep_with_comma(srcWord, trgWord, args);

        frsArgType = get_arg_type(srcWord);
        secArgType = get_arg_type(trgWord);

        if (frsArgType == REGISTER_METHOD && secArgType == REGISTER_METHOD)
            /* The combined register addressing method requires only 1 additional memWord */
            return 1;
        else
            /* All the other cases with 2 operands requires 2 additional words */
            return 2;
    }
    else {
        /* Here we have either one operand or jump with parameters */
        take_first_word_from_line(JmpWord, argsCpy);
        frsArgType = get_arg_type(JmpWord);

        if (frsArgType == IMMEDIATE_METHOD || frsArgType == DIRECT_METHOD || frsArgType == REGISTER_METHOD)
            /* One operand case */
            return 1;
        else {
            /* Jump with parameters case */
            take_label_of_jmp_met(argsCpy, jmpLabel);
            take_next_arg_from_parentheses(argsCpy, srcWord);
            take_next_arg_from_parentheses(argsCpy, trgWord);

            if (is_register(srcWord) && is_register(trgWord))
                /* Jump with parameter with combined register addressing method */
                return 2;
            else
                /* Jump with parameter with different args */
                return 3;
        }
    }
}

void take_label_of_jmp_met(char *wholeJmpWord, char *label) {
    char *end;
    size_t labelLength;
    /* Reset the output buffer */
    label[0] = '\0';

    while (*wholeJmpWord != '\0' && isspace(*wholeJmpWord))
        wholeJmpWord++;

    if ((end = strchr(wholeJmpWord, '(')) != NULL) {
        labelLength = end - (wholeJmpWord + 1);

        strncpy(label, wholeJmpWord + 1, labelLength);
        label[labelLength] = '\0';
    }

}

cmdOpCode get_cmd_op_code(char *cmdName) {

    if (!strcmp(cmdName,MOV_W))
        return MOV;
    if (!strcmp(cmdName,CMP_W))
        return CMP;
    if (!strcmp(cmdName,CMP_W))
        return CMP;
    if (!strcmp(cmdName,ADD_W))
        return ADD;
    if (!strcmp(cmdName,SUB_W))
        return SUB;
    if (!strcmp(cmdName,NOT_W))
        return NOT;
    if (!strcmp(cmdName,CLR_W))
        return CLR;
    if (!strcmp(cmdName,LEA_W))
        return LEA;
    if (!strcmp(cmdName,INC_W))
        return INC;
    if (!strcmp(cmdName,DEC_W))
        return DEC;
    if (!strcmp(cmdName,JMP_W))
        return JMP;
    if (!strcmp(cmdName,BNE_W))
        return BNE;
    if (!strcmp(cmdName,RED_W))
        return RED;
    if (!strcmp(cmdName,PRN_W))
        return PRN;
    if (!strcmp(cmdName,JSR_W))
        return JSR;
    if (!strcmp(cmdName,RTS_W))
        return RTS;
    if (!strcmp(cmdName,STOP_W))
        return STOP;

    return -1;   /* undefined command */
}

/* From the right side:
     * bits 2-3: source operand addressing method
     * bits 4-5: target/destination operand addressing method
     * bits 10-11: second parameter addressing method
     * bits 12-13: first parameter addressing method */
bool is_more_words_to_build(CmdWord frsWrd) {
    short srcBits, trgBits, frsParBits, secParBits;

    srcBits = take_src_bits_from_memWord(frsWrd);
    trgBits = take_trg_bits_from_memWord(frsWrd);

    /* source bits cases */
    switch (srcBits) {
        case IMMEDIATE_METHOD:
        case REGISTER_METHOD:
            return TRUE;

        case DIRECT_METHOD:
            if (trgBits != DIRECT_METHOD)
                return FALSE;

        case JMP_WITH_PARAM_METHOD:
            frsParBits = take_frs_par_bits_from_memWord(frsWrd);
            secParBits = take_sec_par_bits_from_memWord(frsWrd);

            if (frsParBits == DIRECT_METHOD && secParBits == DIRECT_METHOD)
                return FALSE;
            else
                return TRUE;

        default:
            break;
    }

    /* target bits cases */
    switch (trgBits) {
        case IMMEDIATE_METHOD:
        case REGISTER_METHOD:
            return TRUE;

        case DIRECT_METHOD:
            return FALSE;

        default:
            break;
    }

    return FALSE;
}

FirstMemWord get_cmd_frs_word(cmdOpCode opCode, char *argsBuff) {

    char srcWord[MAX_NAME_LEN], trgWord[MAX_NAME_LEN], oneOpWord[MAX_LINE_LEN];
    CmdWord result;
    result = initiate_CmdWord_to_zero();

    /* first fill the command op code and A/R/E */
    result.word.frsWord.opcode = opCode;
    result.word.frsWord.A_R_E = ABSOLUTE_A;

    /* in cases of the first command words group - 2 operands */
    if (opCode < NOT || opCode == LEA) {
        take_two_words_sep_with_comma(srcWord, trgWord, argsBuff);

        result.word.frsWord.src_op = get_arg_type(srcWord);
        result.word.frsWord.trg_op = get_arg_type(trgWord);
    }
    else if(opCode < RTS) {
        /* in cases of the second command words group - one operand */
        take_first_word_from_line(oneOpWord, argsBuff);
        result.word.frsWord.trg_op = get_arg_type(oneOpWord);

        if (get_arg_type(oneOpWord) == JMP_WITH_PARAM_METHOD) {
            /* In the cases of the jump with parameters addressing method, we add the bits of the parameters */

            /* change to take two words inside par*/
            take_next_arg_from_parentheses(oneOpWord, srcWord);
            take_next_arg_from_parentheses(oneOpWord, trgWord);

            result.word.frsWord.frs_parm = get_arg_type(srcWord);
            result.word.frsWord.sec_parm = get_arg_type(trgWord);
        }
        else
            /* here we have only one operand to update inside the memory memWord */
            result.word.frsWord.trg_op = get_arg_type(oneOpWord);
    }

    /* In the cases of RTS and STOP, we only need to update the operation code inside the memory memWord */
    return result.word.frsWord;
}

SrcRegMemWord get_src_reg_word(char *arg) {
    MemWord result;
    regNum regNumb;
    result = initiate_memWord_to_zero();
    result.wordType.srcRegWord.A_R_E = ABSOLUTE_A;

    regNumb = get_num_of_register(arg);
    switch (regNumb) {
        case r0:
            result.wordType.srcRegWord.content = r0;
            break;
        case r1:
            result.wordType.srcRegWord.content = r1;
            break;
        case r2:
            result.wordType.srcRegWord.content = r2;
            break;
        case r3:
            result.wordType.srcRegWord.content = r3;
            break;
        case r4:
            result.wordType.srcRegWord.content = r4;
            break;
        case r5:
            result.wordType.srcRegWord.content = r5;
            break;
        case r6:
            result.wordType.srcRegWord.content = r6;
            break;
        case r7:
            result.wordType.srcRegWord.content = r7;
            break;
        default:
            break;
    }

    return result.wordType.srcRegWord;
}

TarRegMemWord get_tar_reg_word(char *arg) {
    MemWord result;
    regNum regNumb;
    result = initiate_memWord_to_zero();
    result.wordType.tarRegWord.A_R_E = ABSOLUTE_A;

    regNumb = get_num_of_register(arg);
    switch (regNumb) {
        case r0:
            result.wordType.tarRegWord.content = r0;
            break;
        case r1:
            result.wordType.tarRegWord.content = r1;
            break;
        case r2:
            result.wordType.tarRegWord.content = r2;
            break;
        case r3:
            result.wordType.tarRegWord.content = r3;
            break;
        case r4:
            result.wordType.tarRegWord.content = r4;
            break;
        case r5:
            result.wordType.tarRegWord.content = r5;
            break;
        case r6:
            result.wordType.tarRegWord.content = r6;
            break;
        case r7:
            result.wordType.tarRegWord.content = r7;
            break;
        default:
            break;
    }

    return result.wordType.tarRegWord;
}

DoubleRegMemWord get_comb_reg_word(char *argsBuff) {
    char frsArg[MAX_NAME_LEN], secArg[MAX_NAME_LEN];
    MemWord result;
    regNum regNum1, regNum2;
    result = initiate_memWord_to_zero();

    result.wordType.combRegWord.A_R_E = ABSOLUTE_A;
    take_two_words_sep_with_comma(frsArg, secArg, argsBuff);

    regNum1 = get_num_of_register(frsArg);
    regNum2 = get_num_of_register(secArg);

    switch (regNum1) {
        case r0:
            result.wordType.combRegWord.src_content = r0;
            break;
        case r1:
            result.wordType.combRegWord.src_content = r1;
            break;
        case r2:
            result.wordType.combRegWord.src_content = r2;
            break;
        case r3:
            result.wordType.combRegWord.src_content = r3;
            break;
        case r4:
            result.wordType.combRegWord.src_content = r4;
            break;
        case r5:
            result.wordType.combRegWord.src_content = r5;
            break;
        case r6:
            result.wordType.combRegWord.src_content = r6;
            break;
        case r7:
            result.wordType.combRegWord.src_content = r7;
            break;
        default:
            break;
    }

    switch (regNum2) {
        case r0:
            result.wordType.combRegWord.tar_content = r0;
            break;
        case r1:
            result.wordType.combRegWord.tar_content = r1;
            break;
        case r2:
            result.wordType.combRegWord.tar_content = r2;
            break;
        case r3:
            result.wordType.combRegWord.tar_content = r3;
            break;
        case r4:
            result.wordType.combRegWord.tar_content = r4;
            break;
        case r5:
            result.wordType.combRegWord.tar_content = r5;
            break;
        case r6:
            result.wordType.combRegWord.tar_content = r6;
            break;
        case r7:
            result.wordType.combRegWord.tar_content = r7;
            break;
        default:
            break;
    }

    return result.wordType.combRegWord;
}


AddiMemWord get_immediate_word(char *arg) {
    MemWord result;
    int num;
    result = initiate_memWord_to_zero();

    remove_char_from_string(arg, '#');
    take_next_integer(arg, &num);

    result.wordType.addiWord.A_R_E = ABSOLUTE_A;
    result.wordType.addiWord.content = num;

    return result.wordType.addiWord;
}

extern pNode listHead;

AddiMemWord get_label_addr_memWord_from_table(char labelName[10], int IC) {
    MemWord result;
    pNode currNode;
    result = initiate_memWord_to_zero();

    /* Find the label inside the symbol table */
    currNode = search_label_node(labelName, listHead);

    if (currNode == NULL)
        return result.wordType.addiWord;

    if (currNode->content.EntOrExt == external) {
        /* hold a list of externals usage for the externals file */
        add_external_operand_to_exList(currNode, IC);
        /* The label assign as extern so the content is 0, and the A/R/E - external*/
        result.wordType.addiWord.content = 0;
        result.wordType.addiWord.A_R_E = EXTERNAL_A;
    }
    else {
        /* Assign the address value of the symbol table node as the content of the memory memWord,
         * and the attribute is relocatable as we know the address only on the second pass */
        result.wordType.addiWord.A_R_E = RELOCATABLE_A;
        result.wordType.addiWord.content = currNode->content.value;
    }

    return result.wordType.addiWord;
}

int complete_coding_words(int IC, char *line, bool *err_flag) {
    char wordBuff1[MAX_NAME_LEN], wordBuff2[MAX_NAME_LEN];  /* the name of the command */
    CmdWord result;                                         /* the label addressing memWord */
    int addWord = 1, i;                                    /* number of words per command to add */
    result = initiate_CmdWord_to_zero();

    addWord += get_command_num_of_addi_memWords(line);
    /* remove the command at the start of the line */
    take_first_word_from_line(wordBuff1, line);
    remove_word_from_string(line, wordBuff1);
    line = eliminate_left_whites(line);

    /* find if the memory memWord is empty or full, if empty - complete the coding */
    for (i = IC; i < IC + addWord; i++) {
        if ((cmdImage[i].empty) == ON) {

            if (strchr(line, '(')){
                if (line[0] != '(') {
                    take_label_from_arg(wordBuff1, line, err_flag);
                    remove_word_from_string(line, wordBuff1);
                    result.word.addiWord = get_label_addr_memWord_from_table(wordBuff1, i);
                    cmdImage[i].memWord = result;
                    cmdImage[i].memWord.typeNum = addiWord;
                    cmdImage[i].empty = OFF;
                }
                else {
                    take_next_arg_from_parentheses(line, wordBuff1);
                    take_next_arg_from_parentheses(line, wordBuff2);

                    if (get_arg_type(wordBuff1) == DIRECT_METHOD) {
                        result.word.addiWord = get_label_addr_memWord_from_table(wordBuff1, i);
                        cmdImage[i].memWord = result;
                        cmdImage[i].memWord.typeNum = addiWord;
                        cmdImage[i].empty = OFF;
                        ++i;
                    }
                    if (get_arg_type(wordBuff2) == DIRECT_METHOD) {
                        result.word.addiWord = get_label_addr_memWord_from_table(wordBuff2, i);
                        cmdImage[i + 1].memWord = result;
                        cmdImage[i + 1].memWord.typeNum = addiWord;
                        cmdImage[i + 1].empty = OFF;
                    }
                }
            }
            else {
                take_two_words_sep_with_comma(wordBuff1, wordBuff2, line);

                if (get_arg_type(wordBuff1) == DIRECT_METHOD) {
                    result.word.addiWord = get_label_addr_memWord_from_table(wordBuff1, i);
                    cmdImage[i].memWord = result;
                    cmdImage[i].memWord.typeNum = addiWord;
                    cmdImage[i].empty = OFF;
                } else {
                    result.word.addiWord = get_label_addr_memWord_from_table(wordBuff2, i);
                    cmdImage[i].memWord = result;
                    cmdImage[i].memWord.typeNum = addiWord;
                    cmdImage[i].empty = OFF;
                }
            }
        }
    }

    return addWord;
}
