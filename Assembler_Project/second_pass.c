#include "main_header.h"
extern pNode listHead;
extern int lineNum;

/* the memory image array of the program */
MemoryLine memImage[MEMORY_SIZE];

extern DataWord dataImage[MEMORY_SIZE];

extern CmdLine cmdImage[MEMORY_SIZE];

void second_pass(FILE *pFile, int *pIC, int DC, bool *err_flag) {
    int L;                              /* for length of words per commend */
    char lineBuff[MAX_LINE_LEN],        /* for the line from the file */
    labelBuff[MAX_NAME_LEN], wordBuff[WORD_BUFF_LEN];            /* to handel all kinds of labels at the start of the line */
    *pIC = FIRST_MEMORY_PLACE;
    lineNum = 0;

    /* Start again from the beginning of the input file*/
    rewind(pFile);

    while (read_next_src_line(pFile, lineBuff, err_flag)){
        lineNum++;

        if (is_comment(lineBuff))
            continue;
        /* step 3 - nothing */
        if (is_label_ahead(lineBuff)) { /* step 3 of the algo */
            take_first_word_from_line(labelBuff, lineBuff);
            remove_word_from_string(lineBuff, labelBuff);
        }

        take_first_word_from_line(wordBuff, lineBuff);

        if(!is_extern(wordBuff) && !is_data_ahead(wordBuff, err_flag)){
            if (is_entry(wordBuff))
                update_entries_in_table(lineBuff);
            else {
                /* step 7 */
                /* using label buff as a casual buffer */
                if (is_data_ahead(wordBuff, err_flag))
                    continue;
                L = complete_coding_words(*pIC, lineBuff, err_flag);
                *pIC += L;
            }
        }
    }
    /* step 10 - in the processor file */

    build_unified_memory_image(*pIC, DC);
}

void build_unified_memory_image(int IC, int DC) {
    int i,j;

    for (i = FIRST_MEMORY_PLACE; i < IC; i++) {
        memImage[i].address = i;
        memImage[i].cmdWord = cmdImage[i].memWord;
        memImage[i].memType = cmdType;
    }

    for (i = IC, j = 0; i < IC + DC; i++, j++) {
        memImage[i].address = i;
        memImage[i].dataWord = dataImage[j];
        memImage[i].memType = dataType;
    }

}
