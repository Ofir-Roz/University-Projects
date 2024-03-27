#include "main_header.h"
extern pNode listHead;
extern pNode extrnList;
extern int lineNum;

extern MemoryLine memImage[MEMORY_SIZE];

char *from_int_to_bin(unsigned short parm, int binRepLen, char *buff);

void output_file_builder(char *file_name, int finalIC, int finalDC) {
    int endOfName;

    trim_file_name(file_name);

    build_obj_file(file_name, finalIC, finalDC);

    trim_file_name(file_name);

    if (is_there_extern_entry_in_symbol_table(ENTRY_CHAR)) {
        build_entries_file(file_name);

        endOfName = (int) strlen(file_name);
        /* Put null terminator 4 spots before the end of the string */
        file_name[endOfName - 4] = '\0';
    }

    if (is_there_extern_entry_in_symbol_table(EXTERN_CHAR)){
        build_extern_file(file_name);
    }

    free_label_list(listHead);
    free_label_list(extrnList);
}

void build_obj_file(char *fileName, int finalIC, int finalDC) {
    int i;
    char lineToPost[MAX_LINE_LEN];
    FILE *pFile;

    /* Add new file ending - .ob */
    strcat(fileName, ".ob");
    pFile = fopen(fileName, "w");

    /* First line : the length of the instructions part and the length of the data part */
    fprintf(pFile,"\t%d %d\n", finalIC - FIRST_MEMORY_PLACE, finalDC);

    for (i = FIRST_MEMORY_PLACE; i < finalIC + finalDC; i++) {
        translate_memword_to_obj_line(memImage[i], lineToPost);
        change_for_special_base(lineToPost);
        fprintf(pFile, "%s\n", lineToPost);
    }

    fclose(pFile);
}

void translate_memword_to_obj_line(MemoryLine memLine, char lineBuff[MAX_LINE_LEN]) {
    char number[MAX_NAME_LEN];

    switch (memLine.memType) {
        case dataType:
            sprintf(lineBuff, "%04d\t\t%s", memLine.address, from_int_to_bin(memLine.dataWord.data, 14, number));
            break;

        case cmdType:
            switch (memLine.cmdWord.typeNum) {
                case frsWord:
                    sprintf(lineBuff, "%04d\t\t", memLine.address);
                    strcat(lineBuff, from_int_to_bin(memLine.cmdWord.word.frsWord.frs_parm, 2, number));
                    strcat(lineBuff, from_int_to_bin(memLine.cmdWord.word.frsWord.sec_parm, 2, number));
                    strcat(lineBuff, from_int_to_bin(memLine.cmdWord.word.frsWord.opcode, 4, number));
                    strcat(lineBuff, from_int_to_bin(memLine.cmdWord.word.frsWord.src_op, 2, number));
                    strcat(lineBuff, from_int_to_bin(memLine.cmdWord.word.frsWord.trg_op, 2, number));
                    strcat(lineBuff, from_int_to_bin(memLine.cmdWord.word.frsWord.A_R_E, 2, number));
                    break;

                case addiWord:
                    sprintf(lineBuff, "%04d\t\t", memLine.address);
                    strcat(lineBuff, from_int_to_bin(memLine.cmdWord.word.addiWord.content, 12, number));
                    strcat(lineBuff, from_int_to_bin(memLine.cmdWord.word.addiWord.A_R_E, 2, number));
                    break;

                case tarWord:
                    sprintf(lineBuff, "%04d\t\t", memLine.address);
                    strcat(lineBuff,from_int_to_bin(memLine.cmdWord.word.tarRegWord.space, 6, number));
                    strcat(lineBuff,from_int_to_bin(memLine.cmdWord.word.tarRegWord.content, 6, number));
                    strcat(lineBuff,from_int_to_bin(memLine.cmdWord.word.tarRegWord.A_R_E, 2, number));
                    break;

                case srcWord:
                    sprintf(lineBuff, "%04d\t\t", memLine.address);
                    strcat(lineBuff,from_int_to_bin(memLine.cmdWord.word.srcRegWord.content, 6, number));
                    strcat(lineBuff,from_int_to_bin(memLine.cmdWord.word.srcRegWord.space, 6, number));
                    strcat(lineBuff,from_int_to_bin(memLine.cmdWord.word.srcRegWord.A_R_E, 2, number));
                    break;

                case combWord:
                    sprintf(lineBuff, "%04d\t\t", memLine.address);
                    strcat(lineBuff,from_int_to_bin(memLine.cmdWord.word.combRegWord.src_content, 6, number));
                    strcat(lineBuff,from_int_to_bin(memLine.cmdWord.word.combRegWord.tar_content, 6, number));
                    strcat(lineBuff,from_int_to_bin(memLine.cmdWord.word.combRegWord.A_R_E, 2, number));
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

char *from_int_to_bin(unsigned short parm, int binRepLen, char *buff) {
    int i;

    for (i = binRepLen - 1; i >= 0; i--) {
        buff[i] = (parm & 1) + '0';
        parm >>= 1;
    }

    buff[binRepLen] = '\0';

    return &buff[0];
}

void change_for_special_base(char post[MAX_LINE_LEN]) {
    int i;

    /* Starting from char no.6 - after the address of the line */
    for (i = 6; i < strlen(post); i++) {
        if (post[i] == '0')
            post[i] = '.';
        if (post[i] == '1')
            post[i] = '/';
    }
}

void build_extern_file(char *fileName) {
    FILE *pFile;
    pNode currNode;

    /* Add new file ending - .ext */
    strcat(fileName, ".ext");
    pFile = fopen(fileName, "w");
    currNode = extrnList;

    while (currNode != NULL) {

        if (currNode->content.EntOrExt == external)
            fprintf(pFile, "%s\t\t%i\n", currNode->name, currNode->content.value);

        currNode = currNode->next;
    }
}

void build_entries_file(char *fileName) {
    FILE *pFile;
    pNode currNode;

    /* Add new file ending - .ent */
    strcat(fileName, ".ent");
    pFile = fopen(fileName, "w");
    currNode = listHead;

    while (currNode != NULL) {

        if (currNode->content.EntOrExt == entry)
            fprintf(pFile, "%s\t\t%i\n", currNode->name, currNode->content.value);

        currNode = currNode->next;
    }
}

void post_line_in_file(FILE *pFile, char *string) {
    char *c;

    if (pFile == NULL) {
        printf("Error: invalid file pointer\n");
        return;
    }

    if ((c = strchr(string, '\r')))
        *c = '\n';
    else
        strcat(string,"\n");

    fprintf(pFile, "%s", string);
}

bool read_next_src_line(FILE *pFile, char *pString, bool *errFlag) {
    int i = 0;
    char c;

    while ((c = (char)fgetc(pFile)) != EOF) {
        if (c == '\n') {
            pString[i] = '\0';
            return TRUE;
        }

        pString[i++] = c;
        if (i >= MAX_LINE_LEN - 1) {
            pString[i] = '\0';
            *errFlag = ON;
            print_err_or_warn("Source file line is too long", ERROR, lineNum);
            return FALSE;
        }
    }

    pString[i] = '\0';
    return i > 0;
}

void update_file_path(char *fileName,char *filePath) {
    char *cwd = malloc(sizeof(char) * MAX_PATH_LENGTH);

    if (cwd == NULL) {
        printf("Error allocating memory\n");
        return;
    }
    if (getcwd(cwd, MAX_PATH_LENGTH) == NULL) {
        printf("Error getting current working directory\n");
        free(cwd);
        return;
    }

    strcpy(filePath, cwd);
    strcat(filePath, "/");
    strcat(filePath, fileName);
    free(cwd);
}

void trim_file_name(char *fileName) {
    int endOfName;

    endOfName = (int) strlen(fileName);

    /* Put null terminator 3 spots before the end of the string */
    fileName[endOfName - 3] = '\0';
}
