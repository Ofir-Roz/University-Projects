#ifndef ASSEMBLER_STRING_MANIPULATIONS_H
#define ASSEMBLER_STRING_MANIPULATIONS_H

/**
 * Function to add ending for a given file name. The function add ".as" to the end of the string.
 * @param file_name the name of the file
 * @return The modified file name with the ending ".as"
 */
char *file_ending_adder(char *file_name);

/**
 * Function for jump over the leading white chars of a given string.
 * @param string the given string
 * @return The string where the graphic chars start
 */
char *eliminate_left_whites(char *string);

/**
 * Method for remove a memWord from a given string.
 * @param string the string to modify
 * @param wordBuff the memWord to remove from the string
 */
void remove_word_from_string(char *string, const char *wordBuff);

/**
 * Function for getting the first memWord of a given string
 * @param wordBuff buffer for the memWord output
 * @param line the string to take the memWord from
 * @return pointer to the wordBuff string
 */
char *take_first_word_from_line(char *wordBuff, char *line);

/**
 * Method for extracting a ascii string from quotation marks. exp: gets " blabla" , out:  blabla.
 * @param buff buffer for the output string
 * @param string the given string with the quotation marks
 */
void extract_string_from_quotation_marks(char buff[ASCII_BUFF_LEN], char *string);

/**
 * Function for getting the next character of a given string. than removes it from the string.
 * @param buff the string
 * @return A char, the first one of the string
 */
char take_next_char(char buff[ASCII_BUFF_LEN]);

/**
 * Function that get a string full of numbers from the next kind: " 24, 55, -11  , 50".
 * The function returns the next close number and removes it from the original string.
 * @param string the string of numbers
 * @return A converted number into integer
 */
char * take_next_integer(char *string, int *intBuff);

/**
 * Function for getting the arguments part of an assembly line, right after the command memWord.
 * @param argsBuff the buffer to fill the arguments in
 * @param line the given line to take the arguments from
 */
void take_args_of_cmd(char *argsBuff, char *line);

/**
 * Function for getting the next arg in a given arguments string from the kind of " #1,  END", output: "#1"
 * @param argsBuff the string of the arguments
 * @param soleArg the buffer for the sole arg
 * @return pointer to soleArg
 */
char *get_next_arg(char *argsBuff, char *soleArg);

/**
 * Function to take the arguments inside the parentheses, one after another
 * (for the jump with parameters addressing method)
 * @param expression all the expression including the label and the parenthesis
 * @return pointer to the next starting point of the argument inside -> ()
 */
char *take_next_arg_from_parentheses(char *expression, char *soleArg);

/**
 * Function for getting a label name from an argument string of the kind - "LOOP(K,END)", output: "LOOP".
 * The "Jump with arguments" addressing method.
 * @param buff the buffer to put the label into
 * @param string the string to take the label from
 * @param errFlag for handling errors - illegal label or label not fount on the tabel
 */
void take_label_from_arg(char buff[MAX_NAME_LEN], char *string, bool *errFlag);

/**
 * Function for getting a label name from an argument string of the kind - "LOOP(K,END)", output: "LOOP".
 * The "Jump with arguments" addressing method.
 * @param buff the buffer to put the label into
 * @param string the string to take the label from
 */
void take_label_from_arg_no_err(char buff[MAX_NAME_LEN], char *string);

/**
 * Simple method for trimming the white chars from a given string
 * @param str the given string to modify
 */
void trim_whitespace(char *str);

/**
 * Function for getting two words seperated by one comma, into the buffers. "word1,  word2 " , output: "word1" , "word2"
 * @param arg1 buffer for the first memWord
 * @param arg2 buffer for the second memWord
 * @param args the string to take the words from
 */
void take_two_words_sep_with_comma(char arg1[MAX_NAME_LEN], char arg2[MAX_NAME_LEN], char *args);

/**
 * Function for validate if there is comma in a given string
 * @param input_string the given string
 * @return True if the string contains a comma
 */
bool is_contains_comma(const char* input_string);

/**
 * Function for checking if there is only one memWord in a given string
 * @param input_string the given string
 * @return True if the string contains only one memWord
 */
bool is_contains_one_word_only(const char* input_string);

/**
 * Function for checking if there is only white characters in a given string
 * @param input_string the given string
 * @return True if there is only white chars in the string
 */
bool is_contains_whites_only(const char* input_string);

/**
 * Simple Function for removing character instances from a string
 * @param str the given string to modify
 * @param c the character to remove from the string
 */
void remove_char_from_string(char *str, char c);

#endif
