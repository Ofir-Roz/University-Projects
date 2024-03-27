#include "main_header.h"
extern int lineNum;

char *file_ending_adder(char *file_name){
    char *p;
    char *file_end= ".as";

    p = (char *) malloc(strlen(file_name) + strlen(file_end) + 1); /* +1 for '\0'*/
    if (p == NULL){
        printf("\nCannot allocate memory.");
        exit(0);
    }
    strcpy(p, file_name);
    strcat(p,file_end);
    return p;
}

char *eliminate_left_whites(char *string)
{
    while (isspace(*string) && *string != '\0')
        string++;
    return string;
}

void remove_word_from_string(char *string, const char *wordBuff) {
    int i, j, k;
    int wordLen =(int)strlen(wordBuff);
    int strLen = (int)strlen(string);
    bool wordFound = FALSE;

    /* No word to remove */
    if (wordLen == 0)
        return;

    /* Iterate through the string */
    for (i = 0; i <= strLen - wordLen; i++) {
        /* Check if wordBuff is found at current position */
        wordFound = TRUE;
        for (j = 0, k = i; wordBuff[j] != '\0'; j++, k++) {
            if (string[k] != wordBuff[j]) {
                wordFound = FALSE;
                break;
            }
        }

        /* If wordBuff is found, remove it from the string */
        if (wordFound) {
            /* Shift characters after wordBuff to the left */
            for (j = i + wordLen, k = i; string[j] != '\0'; j++, k++) {
                string[k] = string[j];
            }
            string[k] = '\0';
            i--;
        }
    }
}

char *take_first_word_from_line(char *wordBuff, char *line) {

    while (*line && isspace(*line))
        line++;

    while (*line && !isspace(*line)) {
        *wordBuff++ = *line++;
        /* if (*line == ',')
            break;
            */
    }

    *wordBuff = '\0';

    return wordBuff;
}

void extract_string_from_quotation_marks(char buff[ASCII_BUFF_LEN], char *string) {
    int length;
    string = eliminate_left_whites(string);
    length = (int)strlen(string);

    /* Check if the string is empty or does not start with a quotation mark */
    if (length < 2 || string[0] != '\"' || string[length - 1] != '\"') {
        buff[0] = '\0';  /* Set the output buffer as empty */
        return;
    }

    /* Copy the characters between the quotation marks to the output buffer  */
    strncpy(buff, string + 1, length - 2);
    buff[length - 2] = '\0';  /* Add null terminator to the output buffer */
}

char take_next_char(char buff[ASCII_BUFF_LEN]) {
    int i;
    char nextChar;

    /* Check if the buffer is empty */
    if (strlen(buff) == 0) {
        return '\0';  /* Return null character if buffer is empty */
    }

    nextChar = buff[0];

    /* Shift the characters in the buffer to the left */
    for (i = 0; i < strlen(buff); i++) {
        buff[i] = buff[i + 1];
    }

    return nextChar;
}

char *take_next_integer(char *string, int *intBuff) {
    bool negative = FALSE;
    *intBuff = 0;

    if (*string == '\0')
        return NULL;

    while (isspace(*string))
        string++;

    if (*string == '-') {
        negative = TRUE;
        string++;
    }

    while (isdigit(*string)) {
        *intBuff = (*intBuff * 10) + (*string - '0');
        string++;
    }

    if (negative)
        *intBuff = -*intBuff;

    while (isspace(*string) || *string == ',') {
        string++;
    }

    return string;
}

void take_args_of_cmd(char *argsBuff, char *line) {
    char wordBuff[WORD_BUFF_LEN];

    line = eliminate_left_whites(line);
    strcpy(argsBuff, line);

    take_first_word_from_line(wordBuff, argsBuff);
    remove_word_from_string(argsBuff, wordBuff);

}

char *get_next_arg(char *argsBuff, char *soleArg) {

    take_first_word_from_line(soleArg, argsBuff);

    if (!strcmp(soleArg, ",")) {
        remove_word_from_string(argsBuff, ",");
        take_first_word_from_line(soleArg, argsBuff);
    }

    if (soleArg[0] == ',' || soleArg[(strlen(soleArg) - 1)] == ',')
        remove_char_from_string(soleArg, ',');

    remove_word_from_string(argsBuff, soleArg);

    return soleArg;
}

char *take_next_arg_from_parentheses(char *expression, char *soleArg) {
    char *start = strchr(expression, '(');
    char *end = strchr(expression, ')');

    if (start == NULL || end == NULL) {
        soleArg[0] = '\0';
    } else {
        size_t length = end - start - 1;

        char *comma = strchr(start + 1, ',');
        if (comma != NULL && comma < end) {
            length = comma - start - 1;
            end = comma;
        }

        strncpy(soleArg, start + 1, length);
        soleArg[length] = '\0';

        char *src = end + 1;
        char *dst = start + 1;
        while ((*dst++ = *src++)) {}
    }

    start = strchr(expression, '(');
    end = strchr(expression, ')');

    if (start != NULL && end == NULL)
        strncat(expression, "\0", strlen(expression) - 2);

    return soleArg;
}

void take_label_from_arg(char buff[MAX_NAME_LEN], char *string, bool *errFlag) {
    /* Reset the output buffer */
    buff[0] = '\0';

    while (isspace(*string))
        string++;

    /* Check if the string is enclosed in parentheses */
    if (*string == '(') {
        char *end = strchr(string, ')');

        if (end != NULL) {
            size_t labelLength = end - (string + 1);

            strncpy(buff, string + 1, labelLength);
            buff[labelLength] = '\0';

            memmove(string, end + 1, strlen(end + 1) + 1);
        } else {
            /* Invalid format, copy the entire string to the buffer */
            strcpy(buff, string);
            string[0] = '\0';
        }
    } else {
        /* Check for parentheses or comma to find the end of the label */
        char *end = strchr(string, '(');
        if (end == NULL)
            end = strchr(string, ',');

        if (end != NULL) {
            size_t labelLength = end - string;

            strncpy(buff, string, labelLength);
            buff[labelLength] = '\0';

            memmove(string, end, strlen(end) + 1);
        } else {
            /* No end delimiter found, copy the entire string to the buffer */
            strcpy(buff, string);
            string[0] = '\0';
        }
    }

    /* Check if the label name is legal and if it exists in the table */
    if (isalpha(*buff) && is_label_syntax(buff) && !is_saved_word(buff)) {
        if (!is_label_in_list(buff)) {
            *errFlag = ON;
            print_err_or_warn("Label not fount in the symbol-table.", ERROR, lineNum);
        }
    } else {
        *errFlag = ON;
        print_err_or_warn("Illegal label name", ERROR, lineNum);
    }
}

void take_label_from_arg_no_err(char buff[MAX_NAME_LEN], char *string) {
    /* Reset the output buffer */
    buff[0] = '\0';

    while (isspace(*string))
        string++;

    /* Check if the string is enclosed in parentheses */
    if (*string == '(') {
        char *end = strchr(string, ')');

        if (end != NULL) {
            size_t labelLength = end - (string + 1);

            strncpy(buff, string + 1, labelLength);
            buff[labelLength] = '\0';

            memmove(string, end + 1, strlen(end + 1) + 1);
        } else {
            /* Invalid format, copy the entire string to the buffer */
            strcpy(buff, string);
            string[0] = '\0';
        }
    } else {
        /* Check for parentheses or comma to find the end of the label */
        char *end = strchr(string, '(');
        if (end == NULL)
            end = strchr(string, ',');

        if (end != NULL) {
            size_t labelLength = end - string;

            strncpy(buff, string, labelLength);
            buff[labelLength] = '\0';

            memmove(string, end, strlen(end) + 1);
        } else {
            /* No end delimiter found, copy the entire string to the buffer */
            strcpy(buff, string);
            string[0] = '\0';
        }
    }
}

void trim_whitespace(char *str) {
    int i, j = 0;
    int len = (int)strlen(str);
    char trimmed[MAX_NAME_LEN];

    for (i = 0; i < len; i++) {
        if (!isspace((unsigned char)str[i])) {
            trimmed[j++] = str[i];
        }
    }

    trimmed[j] = '\0';
    strcpy(str, trimmed);
}

void take_two_words_sep_with_comma(char arg1[MAX_NAME_LEN], char arg2[MAX_NAME_LEN], char *args) {
    char *token;
    trim_whitespace(args);

    /* Tokenize the input string using comma as the delimiter */
    token = strtok(args, ",");
    if (token != NULL) {
        strcpy(arg1, token);
        trim_whitespace(arg1);
    }

    token = strtok(NULL, "\n");
    if (token != NULL) {
        strcpy(arg2, token);
        trim_whitespace(arg2);
    }
}

bool is_contains_comma(const char* input_string) {
    while (*input_string) {
        if (*input_string == ',')
            return TRUE;
        input_string++;
    }
    return FALSE;
}

bool is_contains_one_word_only(const char* input_string) {
    int word_count = 0;
    bool in_word = FALSE;

    while (*input_string) {
        if (isspace(*input_string) || *input_string == '\r')
            in_word = FALSE;
        else
            if (!in_word) {
                word_count++;
                in_word = TRUE;
            }

        input_string++;
    }

    return word_count == 1;
}

bool is_contains_whites_only(const char* input_string) {
    while (*input_string) {
        if (!isspace(*input_string))
            return FALSE;
        input_string++;
    }
    return TRUE;
}

void remove_char_from_string(char *str, char c) {
    char *dst;

    if (str == NULL)
        return;

    dst = str;
    while (*str != '\0') {
        if (*str != c) {
            *dst = *str;
            dst++;
        }
        str++;
    }
    *dst = '\0';
}