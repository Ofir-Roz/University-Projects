#ifndef ASSEMBLER_MEMORY_MAP_H
#define ASSEMBLER_MEMORY_MAP_H

/* data words part */

/**
 * Method to dealing with data memWord words on the first pass
 * the method identify the memWord of the data and then insert the translated words from it into
 * the memory image. the method also deals with some errors
 * @param pDC pointer to the next free spot on the memory image
 * @param string the line from the assembly file
 * @param err_flag pointer to the error flag to turn on if there is an error
 */
void identify_and_encrypt_data(int *pDC, char *string, bool *err_flag);

/**
 * Function to translate integer into the binary memWord of the program
 * @param integer the integer to translate from
 * @return the memory memWord
 */
DataWord translate_integer_to_bin(int integer);

/**
 * Function to translate an ascii char into a binary memWord
 * @param chr the character to translate from
 * @return the memory memWord
 */
DataWord translate_ascii_to_bin(char chr);


/* command words part*/

/**
 * Method for building the first command memWord on the memory image and the additional words if needed to
 * @param pIC pointer to the next free spot on the memory image
 * @param line the command line from the assembly file
 */
void build_first_cmd_word_and_more(int *pIC, char *line);

/**
 * Method for build the additional words after the first one on the first pass of the assembler
 * @param pIC pointer to the next free spot on the memory image
 * @param argsBuff all the arguments from the line of the command
 * @param cmdWord the translated first memWord - the command memWord
 */
void build_addi_words_frs_pass(int *pIC, char *argsBuff, CmdWord cmdWord);

/**
 * Method for filling the memory image with additional words of the registers addressing method
 * @param argsBuff all the arguments part from the line for the combined register memWord case
 * @param soleArg the argument to translate in cases of source and target registers
 * @param regMetType the method memWord of the registers - source, target or combo
 * @param pIC pointer to the next free spot on the memory image
 * @param cmdWord the translated first memWord - the command memWord
 */
void fill_addi_words_of_reg_method(char *argsBuff, char *soleArg, int regMetType, int *pIC, CmdWord cmdWord);

/**
 * Function to reveal the memWord of the register addressing method - source, target or combo
 * @param argsBuff the argument part of the line
 * @return SRC_REGISTER_TYPE or TAR_REGISTER_TYPE or COMB_REGISTER_TYPE - numbers
 */
int get_reg_met_type(char *argsBuff);

/**
 * Method for filling the memory image with additional words of the jump with parameter addressing method
 * @param pIC the next free spot on the memory image
 * @param frsParArg the first parameter from inside the parenthesis
 * @param secParArg the second parameter from inside the parenthesis
 * @param cmdWord the translated first memWord - the command memWord
 */
void fill_addi_words_of_param_method(int *pIC, char *frsParArg, char *secParArg, CmdWord cmdWord);

/**
 * Function to find the addressing memWord of the argument
 * @param arg the argument to find
 * @return IMMEDIATE_METHOD or DIRECT_METHOD or JMP_WITH_PARAM_METHOD or REGISTER_METHOD
 */
int get_arg_type(char *arg);

/**
 * Function for getting the number of additional words of the command after the first memWord
 * @param string the command line
 * @return number of additional words to add
 */
int get_command_num_of_addi_memWords(char *string);

/**
 * Function to complete the work of the function above
 * @param args the arguments parts of the line - after the command memWord
 * @return number of additional words
 */
int get_num_of_addi_words_per_cmd( char *args);

/**
 * Function for getting the operational code of a given command memWord
 * @param cmdName the command by name
 * @return cmdOpCode enumeration of commands (from 0 to 15)
 */
cmdOpCode get_cmd_op_code(char *cmdName);

/**
 * Function to check if there is additional words to insert the memory image in the first pass
 * other than the first memWord
 * @param frsWrd the translated first memWord to check if the addressing methods needs additional memory words
 * @return True if there is more words to add
 */
bool is_more_words_to_build(CmdWord frsWrd);

/**
 * Function for building the first memory memWord of a given command
 * @param opCode operation code of the right command
 * @param argsBuff the arguments of the command
 * @return FirstMemWord the translated memory memWord
 */
FirstMemWord get_cmd_frs_word(cmdOpCode opCode, char *argsBuff);

/**
 * Function to get the binary additional memWord of the source register addressing method
 * @param arg the argument to translate from
 * @return SrcRegMemWord the translated memory memWord
 */
SrcRegMemWord get_src_reg_word(char *arg);

/**
 * Function to get the binary additional memWord of the target register addressing method
 * @param arg the argument to translate from
 * @return TarRegMemWord the translated memory memWord
 */
TarRegMemWord get_tar_reg_word(char *arg);

/**
 * Function to get the binary additional memWord of the combined registers addressing method
 * @param argsBuff the argument to translate from
 * @return DoubleRegMemWord the translated memory memWord
 */
DoubleRegMemWord get_comb_reg_word(char *argsBuff);

/**
 * Function to get the binary additional memWord of the immediate addressing method
 * @param arg the argument to translate from
 * @return AddiMemWord the translated memory memWord
 */
AddiMemWord get_immediate_word(char *arg);

/**
 * Function for getting the additional memWord of the label address from the updated symbol table.
 * This process happen on the second pass.
 * @param labelName the label we need to find on the table
 * @return AddiMemWord the address of the label on the memory image
 */
AddiMemWord get_label_addr_memWord_from_table(char labelName[10], int IC);

/**
 * Function for updating the memory image with the uncompleted memory words from the first pass.
 * The function complete the label arguments part with the address of the label.
 * @param pIC the instruction counter pointer
 * @param line the line from the assembly file (without the label on the opening)
 * @param err_flag for handling errors - if some label dont exist in the symbol table
 * @return the number of memory words in the entire line
 */
int complete_coding_words(int IC, char *line, bool *err_flag);

#endif
