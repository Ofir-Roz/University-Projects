
#ifndef ASSEMBLER_ERRORS_H
#define ASSEMBLER_ERRORS_H

/**
 * Method for printing an error to the screen and shot the program right after it. (stdout)
 * @param comment The comment we want to print to the screen
 * @param line_num The number of the current line from the assembly file - for precising the error
 */
void print_err_N_exit(const char *comment, int line_num);

/**
 * Method for printing an error or a warning to the screen (stdout)
 * @param comment The comment we want to print to the screen
 * @param errOrWarn ERROR for errors and WARNING for warning
 * @param line_num The number of the current line from the assembly file - for precising the er
 */
void print_err_or_warn(const char *comment, int errOrWarn, int line_num);

/**
 * Function to check if the line ahead contains a legal command (from the program requirements)
 * @param line the assembly line
 * @param errFlag for handling errors
 * @return True if the command is legal
 */
bool is_legal_command(char *line, bool *errFlag);

/**
 * Function to check if the operands of the command is legal and valid
 * @param line the assembly line
 * @param cmdOpCode the command operation code - for classify the command
 * @return True if the operands are legal
 */
bool is_command_operands_legal(char *line, int cmdOpCode);

/**
 * Function to check if there is only 2 legal operands - operations group no.1 (mov, add...)
 * @param args the operands
 * @return True if there is 2 legal operands
 */
bool is_first_cmd_group_operands_legal(char args[ARGS_BUFF_LEN]);

/**
 * Function to check if there is only 1 legal operand - operations group no.2 (not, clr...)
 * @param args the operand
 * @return True if there is 1 legal operand
 */
bool is_second_cmd_group_operands_legal(char args[ARGS_BUFF_LEN]);

/**
 * Function to check if there is no operands - operations group no.3 (rts, stop)
 * @param args the operands
 * @return True if there is no operands
 */
bool is_third_cmd_group_operands_legal(char args[ARGS_BUFF_LEN]);

/**
 * Function to check if the given new label is legal
 * @param labelName the new label
 * @return True if is the name is legal and free
 */
bool is_new_legal_label(char *labelName);

/**
 * Function to check if the arguments of the ".data" instruction are valid
 * @param args the arguments of the line
 * @return True if the arguments are valid
 */
bool is_legal_data_args(char *args);

/**
 * Function to check if the arguments of the ".string" instruction are valid
 * @param args the arguments of the line
 * @return True if it is an ascii string inside quotation marks
 */
bool is_legal_string_args(char *args);

/**
 * Function to check if the argument of ".entry" or ".extern" instruction is valid
 * @param args the arguments of the line
 * @return True if it is only one name
 */
bool is_legal_extern_entry_args(char *args);

#endif
