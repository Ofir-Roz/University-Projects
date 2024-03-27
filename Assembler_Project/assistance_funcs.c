#include "main_header.h"
extern int lineNum;
/*
 * data section
 */

bool is_data_ahead(char *word, bool *errFlag) {
    word = eliminate_left_whites(word);
    if (word[0] == '.') {
        if (is_data(word) || is_string(word))
            return TRUE;
        else if (!is_extern(word) && !is_entry(word)){
            print_err_or_warn("Instruction not recognized", ERROR, lineNum);
            *errFlag = ON;
        }
    }
    return FALSE;
}

/*
 * labels handling part
 * */

bool is_label_ahead(char *line) {
    return is_label_declaration(line);
}

bool is_label_declaration(char *line) {
    return strchr(line, ':') != NULL ? TRUE : FALSE;
}

bool is_label_syntax(const char *labelName) {
    int i;
    for (i = 0; i < strlen(labelName) ; i++) {
        if (!isalnum(labelName[i])) {
            /* Found a non-alphanumeric character, return false */
            return FALSE;
        }
        if (i > MAX_NAME_LEN - 1)
            /* The name is too long */
            return FALSE;
    }

    return TRUE;
}

/*
 * line validations
 */
bool is_string(char *word) {
    return !strcmp(word, DATA);
}

bool is_data(char *word) {
    return !strcmp(word, STRING);
}

bool is_entry(char *word) {
    return !strcmp(word, ENTRY);
}

bool is_extern(char *word) {
    return !strcmp(word, EXTERNAL);
}

bool is_register(char *word) {
    return ((!strcmp(word, REG_0) || !strcmp(word, REG_1) || !strcmp(word, REG_2) || !strcmp(word, REG_3)
          || !strcmp(word, REG_4) || !strcmp(word, REG_5) || !strcmp(word, REG_6) || !strcmp(word, REG_7)
          )) ? TRUE : FALSE;
}

bool is_comment(char *string)
{
    string = eliminate_left_whites(string);
    return string[0] == ';' ? TRUE : FALSE;
}

bool is_instruction(char *string) {
    return (is_data(string) || is_string(string)
        || is_entry(string) || is_extern(string)) ? TRUE : FALSE;
}

bool is_command_name(char *string) {
    return ((!strcmp(string,MOV_W) || !strcmp(string,CMP_W) || !strcmp(string,ADD_W) || !strcmp(string,SUB_W)
          || !strcmp(string,LEA_W) || !strcmp(string,NOT_W) || !strcmp(string,CLR_W) || !strcmp(string,INC_W)
          || !strcmp(string,DEC_W) || !strcmp(string,JMP_W) || !strcmp(string,BNE_W) || !strcmp(string,RED_W)
          || !strcmp(string,PRN_W) || !strcmp(string,JSR_W) || !strcmp(string,RTS_W) || !strcmp(string,STOP_W))) ? TRUE : FALSE;
}

bool is_saved_word(char *word) {
    return (is_instruction(word) || is_command_name(word) || is_register(word));
}

bool is_only_one_word_in_string(const char *string) {
    int wordCount = 0, i;
    bool insideWord = FALSE;

    /* Iterate through each character in the string */
    for (i = 0; string[i] != '\0'; i++) {
        char currentChar = string[i];

        /* Check if the character is a whitespace */
        if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n') {
            /* If we were inside a memWord, increment the memWord count */
            if (insideWord) {
                wordCount++;
                insideWord = FALSE;
            }
        } else {
            insideWord = TRUE;
        }
    }

    if (string[i] == '\0' && insideWord == TRUE)
        wordCount++;
    /* Check if there was at least one memWord and no more than one memWord in the string */
    if (wordCount == 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

bool is_immediate(char arg1[MAX_NAME_LEN]) {
    arg1 = eliminate_left_whites(arg1);

    if (arg1[0] == '#')
        return TRUE;
    else
        return FALSE;
}

short take_src_bits_from_memWord(CmdWord frsWrd) {
    return (short)frsWrd.word.frsWord.src_op;
}

short take_trg_bits_from_memWord(CmdWord frsWrd) {
    return (short)frsWrd.word.frsWord.trg_op;
}

short take_frs_par_bits_from_memWord(CmdWord frsWrd) {
    return (short)frsWrd.word.frsWord.frs_parm;
}

short take_sec_par_bits_from_memWord(CmdWord frsWrd) {
    return (short)frsWrd.word.frsWord.sec_parm;
}

regNum get_num_of_register(char *arg) {

    if (!strcmp(arg, REG_0))
        return r0;
    if (!strcmp(arg, REG_1))
        return r1;
    if (!strcmp(arg, REG_2))
        return r2;
    if (!strcmp(arg, REG_3))
        return r3;
    if (!strcmp(arg, REG_4))
        return r4;
    if (!strcmp(arg, REG_5))
        return r5;
    if (!strcmp(arg, REG_6))
        return r6;
    if (!strcmp(arg, REG_7))
        return r7;

    else
        return -1;
}

MemWord initiate_memWord_to_zero() {
    MemWord result;

    result.wordType.frsWord.A_R_E = 0;
    result.wordType.frsWord.trg_op = 0;
    result.wordType.frsWord.src_op = 0;
    result.wordType.frsWord.opcode = 0;
    result.wordType.frsWord.sec_parm = 0;
    result.wordType.frsWord.frs_parm = 0;

    result.wordType.addiWord.A_R_E = 0;
    result.wordType.addiWord.content = 0;

    result.wordType.tarRegWord.A_R_E = 0;
    result.wordType.tarRegWord.content = 0;
    result.wordType.tarRegWord.space = 0;

    result.wordType.srcRegWord.A_R_E = 0;
    result.wordType.srcRegWord.space = 0;
    result.wordType.srcRegWord.content = 0;

    result.wordType.combRegWord.A_R_E = 0;
    result.wordType.combRegWord.tar_content = 0;
    result.wordType.combRegWord.src_content = 0;

    result.wordType.dataWord.data = 0;

    return result;
}

CmdWord initiate_CmdWord_to_zero() {
    CmdWord result;

    result.word.frsWord.A_R_E = 0;
    result.word.frsWord.trg_op = 0;
    result.word.frsWord.src_op = 0;
    result.word.frsWord.opcode = 0;
    result.word.frsWord.sec_parm = 0;
    result.word.frsWord.frs_parm = 0;

    result.word.addiWord.A_R_E = 0;
    result.word.addiWord.content = 0;

    result.word.tarRegWord.A_R_E = 0;
    result.word.tarRegWord.content = 0;
    result.word.tarRegWord.space = 0;

    result.word.srcRegWord.A_R_E = 0;
    result.word.srcRegWord.space = 0;
    result.word.srcRegWord.content = 0;

    result.word.combRegWord.A_R_E = 0;
    result.word.combRegWord.tar_content = 0;
    result.word.combRegWord.src_content = 0;

    return result;
}