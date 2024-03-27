#include "main_header.h"
int lineNum;           /* The number of the current line for error handling */

void first_pass(FILE *pFile, int *pIC, int *pDC, bool *err_flag) {
    bool labelDef = FALSE;       /* a flag to indicate of label definition */
    char lineBuff[MAX_LINE_LEN], /* for the line from the file */
    labelBuff[MAX_NAME_LEN],     /* to handel all kinds of labels at the start of the line */
    wordBuff[WORD_BUFF_LEN];     /* to handel the different kinds of assembly words */
    int wordsPerCmd, IC;             /* for length of words per commend */
    lineNum = 0;                 /* the line number for error printing */
    *pDC = 0;
    *pIC = IC = FIRST_MEMORY_PLACE;

    while (read_next_src_line(pFile, lineBuff, err_flag)) {
        wordsPerCmd = 1;
        labelDef = FALSE;
        ++lineNum;

        if (is_comment(lineBuff) || lineBuff[0] == '\n' || lineBuff[0] == '\0')
            continue;

        if (is_label_ahead(lineBuff)) { /* step 3 of the algo */
            take_first_word_from_line(labelBuff, lineBuff);
            remove_word_from_string(lineBuff, labelBuff);
            if (is_new_legal_label(labelBuff))
                labelDef = TRUE;
            else
                *err_flag = ON;
        }

        take_first_word_from_line(wordBuff, lineBuff);

        if (is_data_ahead(wordBuff, err_flag)) { /* step 5 + error handling */
            if (labelDef)
                collect_data_label_name(*pDC, labelBuff, err_flag);
            identify_and_encrypt_data(pDC, lineBuff, err_flag);
        }
        else if (is_extern(wordBuff) || is_entry(wordBuff)) {
            if (is_extern(wordBuff))
                insert_extern_to_table(lineBuff, err_flag, *pIC);
            else {
                take_args_of_cmd(labelBuff, lineBuff);
                if (!is_legal_extern_entry_args(labelBuff)) {
                    *err_flag = ON;
                    print_err_or_warn("Illegal entry args", ERROR, lineNum);
                }
            }
            continue;
        }
        else { /* step 11 */
            if (labelDef)
                collect_code_label_name(*pIC, labelBuff, err_flag);

            if (is_legal_command(lineBuff, err_flag)) { /* + error handling inside */
                wordsPerCmd += get_command_num_of_addi_memWords(lineBuff);
                build_first_cmd_word_and_more(pIC, lineBuff);
                IC += wordsPerCmd;
                *pIC = IC;
            }
        }
    }

    if (*err_flag != ON) { /* step 16 */
        update_IC_data_in_label_table(*pIC); /* adding IC final val to the data section */
        second_pass(pFile, pIC, *pDC, err_flag);
    }
}
