#include "main_header.h"
#include <ctype.h>

extern int lineNum;

void print_err_N_exit(const char *comment, int line_num)
{
    fprintf(stdout, RED_COLOR"\nError in line %d: %s "RESET, line_num, comment);
    exit(-42);
}

void print_err_or_warn(const char *comment, int errOrWarn, int line_num)
{
    if (errOrWarn == ERROR)
        fprintf(stdout, RED_COLOR"\nError in line %d: %s "RESET, line_num, comment);
    else if (errOrWarn==WARNING)
        fprintf(stdout,MAGENTA"\nWarning in line %d: %s "RESET,line_num,comment);
    else
    fprintf(stdout,"\ndebugging in line %d: %s ",line_num,comment);
}

bool is_legal_command(char *line, bool *errFlag) {
    char wordBuff[WORD_BUFF_LEN];
    cmdOpCode cmdOpNum;
    take_first_word_from_line(wordBuff, line);

    /* find if there is no syntax problem in the command name and line*/
    if (is_command_name(wordBuff)) {
        cmdOpNum = get_cmd_op_code(wordBuff);
        /* check the args and print the errors */
        if (is_command_operands_legal(line, cmdOpNum))
            return TRUE;
            /* found error*/
        else {
            *errFlag = ON;
            return FALSE;
        }
    }
    else {
        print_err_or_warn("Error in command name", ERROR, lineNum);
        *errFlag = ON;
        return FALSE;
    }
}

bool is_command_operands_legal(char *line, int cmdOpCode) {
    char argsBuff[ARGS_BUFF_LEN], srcOp[MAX_NAME_LEN], trgOp[MAX_NAME_LEN];
    take_args_of_cmd(argsBuff, line);

    eliminate_left_whites(argsBuff);
    /* switch case for all the commands and then send to functions
     * also print the error*/
    switch (cmdOpCode) {
        case MOV:
            if (is_first_cmd_group_operands_legal(argsBuff)) {
                take_two_words_sep_with_comma(srcOp, trgOp, argsBuff);
                /* only immediate addressing method is restrictive for the target operand */
                if ((get_arg_type(trgOp)) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'mov\' command arguments are illegal", ERROR, lineNum);
            break;

        case CMP:
            if (is_first_cmd_group_operands_legal(argsBuff)) {
                /* all addressing methods are legal for both of the operands */
                return TRUE;
            } else
                print_err_or_warn("\'cmp\' command arguments are illegal", ERROR, lineNum);
            break;

        case ADD:
            if (is_first_cmd_group_operands_legal(argsBuff)) {
                take_two_words_sep_with_comma(srcOp, trgOp, argsBuff);
                /* only immediate addressing method is restrictive for the target operand */
                if ((get_arg_type(trgOp)) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'add\' command arguments are illegal", ERROR, lineNum);
            break;

        case SUB:
            if (is_first_cmd_group_operands_legal(argsBuff)) {
                take_two_words_sep_with_comma(srcOp, trgOp, argsBuff);
                /* only immediate addressing method is restrictive for the target operand */
                if ((get_arg_type(trgOp)) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'sub\' command arguments are illegal", ERROR, lineNum);
            break;

        case LEA:
            if (is_first_cmd_group_operands_legal(argsBuff)) {
                take_two_words_sep_with_comma(srcOp, trgOp, argsBuff);
                /* lea legal operands for the source operand are the direct and the jump methods,
                 * for the target operands - all legal except immediate method */
                if (((get_arg_type(srcOp) == DIRECT_METHOD) || (get_arg_type(srcOp) == JMP_WITH_PARAM_METHOD))
                    && (get_arg_type(trgOp) != IMMEDIATE_METHOD))
                    return TRUE;
            }
            print_err_or_warn("\'lea\' command arguments are illegal", ERROR, lineNum);
            break;

        case NOT:
            if (is_second_cmd_group_operands_legal(argsBuff)) {
                take_first_word_from_line(trgOp, argsBuff);
                /* only the immediate method is restrictive  */
                if (get_arg_type(trgOp) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'not\' command arguments are illegal", ERROR, lineNum);
            break;

        case CLR:
            if (is_second_cmd_group_operands_legal(argsBuff)) {
                take_first_word_from_line(trgOp, argsBuff);
                /* only the immediate method is restrictive  */
                if (get_arg_type(trgOp) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'clr\' command arguments are illegal", ERROR, lineNum);
            break;

        case INC:
            if (is_second_cmd_group_operands_legal(argsBuff)) {
                take_first_word_from_line(trgOp, argsBuff);
                /* only the immediate method is restrictive  */
                if (get_arg_type(trgOp) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'inc\' command arguments are illegal", ERROR, lineNum);
            break;

        case DEC:
            if (is_second_cmd_group_operands_legal(argsBuff)) {
                take_first_word_from_line(trgOp, argsBuff);
                /* only the immediate method is restrictive  */
                if (get_arg_type(trgOp) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'dec\' command arguments are illegal", ERROR, lineNum);
            break;

        case JMP:
            if (is_second_cmd_group_operands_legal(argsBuff)) {
                take_first_word_from_line(trgOp, argsBuff);
                /* only the immediate method is restrictive  */
                if (get_arg_type(trgOp) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'jmp\' command arguments are illegal", ERROR, lineNum);
            break;

        case BNE:
            if (is_second_cmd_group_operands_legal(argsBuff)) {
                take_first_word_from_line(trgOp, argsBuff);
                /* only the immediate method is restrictive  */
                if (get_arg_type(trgOp) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'bne\' command arguments are illegal", ERROR, lineNum);
            break;

        case RED:
            if (is_second_cmd_group_operands_legal(argsBuff)) {
                take_first_word_from_line(trgOp, argsBuff);
                /* only the immediate method is restrictive  */
                if (get_arg_type(trgOp) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'red\' command arguments are illegal", ERROR, lineNum);
            break;

        case PRN:
            if (is_second_cmd_group_operands_legal(argsBuff)) {
                /*all the methods are legal here */
                return TRUE;
            } else
                print_err_or_warn("\'prn\' command arguments are illegal", ERROR, lineNum);
            break;

        case JSR:
            if (is_second_cmd_group_operands_legal(argsBuff)) {
                take_first_word_from_line(trgOp, argsBuff);
                /* only the immediate method is restrictive  */
                if (get_arg_type(trgOp) != IMMEDIATE_METHOD)
                    return TRUE;
            }
            print_err_or_warn("\'jsr\' command arguments are illegal", ERROR, lineNum);
            break;

        case RTS:
            if (is_third_cmd_group_operands_legal(argsBuff)) {
                return TRUE;
            } else
                print_err_or_warn("\'rts\' command arguments are illegal", ERROR, lineNum);
            break;

        case STOP:
            if (is_third_cmd_group_operands_legal(argsBuff)) {
                return TRUE;
            } else
                print_err_or_warn("\'stop\' command arguments are illegal", ERROR, lineNum);
            break;

        default:
            break;
    }
    return FALSE;
}

bool is_first_cmd_group_operands_legal(char args[ARGS_BUFF_LEN]) {
    /* This group has two operands/arguments, seperated by one comma */
    char arg1[MAX_NAME_LEN], arg2[MAX_NAME_LEN];
    int length =(int)strlen(args), wordCount = 0, i;
    bool insideWord = FALSE, commaFound = FALSE;

    /* Iterate through each character in the string */
    for (i = 0; i < length; i++) {
        char currentChar = args[i];

        /* Check if the character is a whitespace */
        if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n') {
            /*  If we were inside a memWord, increment the memWord count */
            if (insideWord) {
                insideWord = FALSE;
                ++wordCount;
            }
        } else if (currentChar == ',') {
            /* Found the comma separator */
            if ((insideWord && !commaFound) || (wordCount == 1 && !commaFound)) {
                commaFound = TRUE;
            } else {
                /* Comma found in an invalid position, return false */
                return FALSE;
            }
        } else {
            insideWord = TRUE;
        }
    }

    /* Check if there are exactly two words separated by one comma */
    if (insideWord && commaFound && wordCount <= 2) {
        take_two_words_sep_with_comma(arg1, arg2, args);

        if ((is_label_syntax(arg1) || (is_register(arg1)) || is_immediate(arg1)) &&
            (is_label_syntax(arg2) || (is_register(arg2)) || is_immediate(arg2)))
        return TRUE;

        else
            return FALSE;
    }
    else
        return FALSE;
}

bool is_second_cmd_group_operands_legal(char args[ARGS_BUFF_LEN]) {
    char argBuff[MAX_LINE_LEN], jmpArg[MAX_NAME_LEN];

    if (is_contains_one_word_only(args)) {
        if (!is_contains_comma(args)) {
            take_first_word_from_line(argBuff, args);
            if (is_label_syntax(argBuff) || (is_register(argBuff)) || is_immediate(argBuff))
                return TRUE;
        } else {
            take_label_from_arg_no_err(argBuff, args);
            if (is_label_syntax(argBuff)) {
                take_next_arg_from_parentheses(args, jmpArg);
                if (is_label_syntax(argBuff) || (is_register(argBuff)) || is_immediate(argBuff)) {
                    take_next_arg_from_parentheses(args, jmpArg);
                    if (is_label_syntax(argBuff) || (is_register(argBuff)) || is_immediate(argBuff))
                        return TRUE;
                }
            }
        }
    }

    return FALSE;
}

bool is_third_cmd_group_operands_legal(char args[ARGS_BUFF_LEN]) {
    return is_contains_whites_only(args);
}

bool is_new_legal_label(char *labelName) {
    remove_char_from_string(labelName, ':');

    if ((isalpha(*labelName) && is_label_syntax(labelName) && !is_label_in_list(labelName) && !is_saved_word(labelName)) == FALSE) {
        print_err_or_warn("Label name is invalid", ERROR, lineNum);
        return FALSE;
    } else
        return TRUE;
}


bool is_legal_data_args(char *args) {
    int length = (int)strlen(args), i;
    bool commaFound = FALSE;
    bool wordStarted = FALSE;

    for (i = 0; i < length; i++) {
        char currentChar = args[i];

        if (isspace(currentChar)) {
            /* Skip white spaces */
            continue;
        }

        if (currentChar == ',') {
            if (commaFound || !wordStarted) {
                /* Multiple commas in a row or comma without a memWord before it */
                return FALSE;
            }

            commaFound = TRUE;
            wordStarted = FALSE;
        }
        else if (isdigit(currentChar) || currentChar == '+' || currentChar == '-') {
            if (!wordStarted) {
                wordStarted = TRUE;
                commaFound = FALSE;
            }
        }
        else {
            /* Invalid character found */
            return FALSE;
        }
    }

    /* Check if the last memWord is followed by a comma */
    if (!wordStarted && commaFound) {
        return FALSE;
    }

    return TRUE;
}

bool is_legal_string_args(char *args) {
    int length = (int)strlen(args), i, j;
    bool insideQuotes = FALSE;
    bool validSequence = FALSE;

    for (i = 0; i < length; i++) {
        char currentChar = args[i];

        if (currentChar == '"') {
            if (insideQuotes) {
                insideQuotes = FALSE;

                if (validSequence && i < length - 1 && args[i + 1] != '\0'
                    && args[i + 1] != ' ' && args[i + 1] != '\t') {
                    /* Next character after the closing quotation mark should be a space or end of string */
                    return FALSE;
                }
                /* check if there is more args after the quotations marks*/
                for (j = i; j < length - 1 ; j++) {
                    if (isgraph(args[j]))
                        return FALSE;
                }
                /* Found a complete valid sequence */
                return TRUE;
            } else {
                insideQuotes = TRUE;
            }
        } else if (insideQuotes) {
            if (!(isascii(currentChar))) {
                /* Non-ASCII character found */
                return FALSE;
            }

            validSequence = TRUE;
        }
    }

    /* Reached the end of string without finding closing quotation mark */
    return FALSE;
}

bool is_legal_extern_entry_args(char *args) {
    args = eliminate_left_whites(args);

    return (is_only_one_word_in_string(args) && isalpha(*args) && is_label_syntax(args) && !is_saved_word(args));
}