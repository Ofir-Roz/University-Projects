#ifndef ASSEMBLER_ASSISTANCE_FUNCS_H
#define ASSEMBLER_ASSISTANCE_FUNCS_H

/**
 * Function to find if the memWord ahead is an instruction memWord/data memWord (.data, .memWord)
 * @param word the memWord from the assembly line
 * @param errFlag for handling error - if the memWord is illegal
 * @return True if it is .data or .memWord. False elsewhere
 */
bool is_data_ahead(char *word, bool *errFlag);

/**
 * Function to find if the line ahead starts with a label
 * @param line the line
 * @return True if there is label on the start
 */
bool is_label_ahead(char *line);

/**
 * Function to find if there is a new label declaration on the given line
 * @param line the line
 * @return True if finds ':' on the line
 */
bool is_label_declaration(char *line);

/**
 * Function to find if a given label is with legal syntax (from the program requirements)
 * @param labelName the label
 * @return True if the syntax is right
 */
bool is_label_syntax(const char *labelName);

/**
 * Function to find if the given memWord is ".string"
 * @param word the memWord
 * @return True if the memWord is ".string"
 */
bool is_string(char *word);

/**
 * Function to find if the given memWord is ".data"
 * @param word the memWord
 * @return True if the memWord is ".data"
 */
bool is_data(char *word);

/**
* Function to find if the given memWord is ".entry"
* @param word the memWord
* @return True if the memWord is ".entry"
*/
bool is_entry(char *word);

/**
 * Function to find if the given memWord is ".extern"
 * @param word the memWord
 * @return True if the memWord is ".extern"
 */
bool is_extern(char *word);

/**
 * Function to find if the given memWord is one of the saved words of the register
 * @param word the memWord
 * @return True if the memWord is one of the registers ("r0", "r1"...)
 */
bool is_register(char *word);

/**
 * Function fo find if the line is an comment line
 * @param string the line
 * @return True if it is a comment line
 */
bool is_comment(char *string);

/**
 * Function to find if the next memWord is an instruction
 * @param string the memWord
 * @return True if the memWord is instruction
 */
bool is_instruction(char *string);

/**
 * Function to find if the next memWord is a command memWord (mov, add, ext..)
 * @param string the memWord
 * @return True if the memWord is a command memWord
 */
bool is_command_name(char *string);

/**
 * Function to find if the next memWord is an assembly saved memWord
 * @param word the memWord
 * @return True if it is a saved memWord
 */
bool is_saved_word(char *word);

/**
 * Function to check if the given string consist only one memWord
 * @param string the given string
 * @return True if there is only one memWord in the string
 */
bool is_only_one_word_in_string(const char *string);

/**
 * Function to check if the next argument/memWord is from the immediate memWord (start with '#')
 * @param arg1 the memWord to check
 * @return True if the memWord is a number starting with #. Else return false
 */
bool is_immediate(char arg1[MAX_NAME_LEN]);

/**
 * Simple function for taking the source operand addressing method bits inside the memory memWord
 * @param frsWrd The first translated memory memWord of some command line
 * @return src_op component - the source operand bits of the memWord
 */
short take_src_bits_from_memWord(CmdWord frsWrd);

/**
 * Simple function for taking the target/destination operand addressing method bits inside the memory memWord
 * @param frsWrd The first translated memory memWord of some command line
 * @return trg_op component - the target operand bits of the memWord
 */
short take_trg_bits_from_memWord(CmdWord frsWrd);

/**
 * Simple function for taking the first argument operand addressing method bits inside the memory memWord -
 * of the jump with parameters addressing method.
 * @param frsWrd The first translated memory memWord of some command line
 * @return frs_parm component - the first argument operand bits of the memWord
 */
short take_frs_par_bits_from_memWord(CmdWord frsWrd);

/**
 * Simple function for taking the second argument operand addressing method bits inside the memory memWord -
 * of the jump with parameters addressing method.
 * @param frsWrd The first translated memory memWord of some command line
 * @return sec_parm component - the second argument operand bits of the memWord
 */
short take_sec_par_bits_from_memWord(CmdWord frsWrd);

/**
 * Simple function for getting the number of the register from an argument/operand
 * @param arg the given argument to find
 * @return regNum the number of the register inside the arg (r0...r7)
 */
regNum get_num_of_register(char *arg);

/**
 * Function for initiating memory memWord fields with 0
 * @return The memory memWord with all fields equals to zero
 */
MemWord initiate_memWord_to_zero();

/**
 * Function for initiating command memWord fields with 0
 * @return The command memWord with all fields equals to zero
 */
CmdWord initiate_CmdWord_to_zero();

#endif