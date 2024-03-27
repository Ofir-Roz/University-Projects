#ifndef ASSEMBLER_PROCESSOR_H
#define ASSEMBLER_PROCESSOR_H

/* Macro is a struct that holds the data of each macro item in the list */
typedef struct mac_node *pMacroNode;
typedef struct mac_node {
    char name[MAX_NAME_LEN];
    char *content;
    pMacroNode next;
} MacroNode;

/**
 * pre_processor is a major method for handling the pre-processor part of the program: mainly to deploy the macros on
 * the original file, and create a new file with the deployed macros, with the ending ".am".
 * @param file_name the original assembly file name
 * @param am_ending_name the new file name with the ending ".am"
 */
void pre_processor(char *file_name, char *am_ending_name);

/**
 * A simple method for starting the process of the coding. the method call to the first pass over the file.
 * @param file_name the file to process the assembly code from
 * @param err_flag for handling errors - stop after the first pass
 */
void code_processor(char *file_name, int *err_flag);

/**
 * Function for getting a macro name from a given string
 * @param string the string with the macro name
 * @param name a buffer for coping the name into
 * @return pointer to the macro name
 */
char *extract_macro_name(const char *string, char *name);

/**
 * Function to collect macro definition and data from the file
 * @param string the line from the macro we need to collect
 * @param name_or_data for identify if we need to collect new name or macro data, 'n' for name, 'd' for data
 * @param mac_name for the name of the macro
 */
void collect_macro(char *string, char name_or_data, char *mac_name);

/**
 * Method for updating new macro name and inserting it into the linked list
 * @param string the string to collect the name from
 */
void collect_new_macro_name(char *string);

/**
 * Method for collecting the macro data/content. The method allocate memory for the data and put it
 * in the macro list.
 * @param name the macro name
 * @param content the content to load into the macro list
 */
void collect_macro_content(const char *name, char *content);

/**
 * Method for deploy the macro data inside a file instead of the macro name.
 * @param pFile the file to post the macro in
 * @param name the name of the macro to post
 */
void deploy_macro_content_in_file(FILE *pFile, char *name);

/**
 * A simple function for detect a if new macro definition is going to be next
 * @param string the line from the original file
 * @return True if there is new macro ahead - found "mcr"
 */
bool is_new_macro_ahead(char *string);

/**
 * Function for finding if the line contain a macro name - for replacing it
 * @param string the original assembly line
 * @return True if the name of the macro exist on the macro list
 */
bool is_macro_name_detected(char *string);

/**
 * Function for finding if a given name is already exist on the macro list
 * @param string the name
 * @return True if the name is already in the list
 */
bool is_mac_name_exist_in_list(char *string);

/**
 * Function to find if the given line indicate the end of the macro definition
 * @param string the given line
 * @return True if it is the end of the definition - found "endmcr"
 */
bool is_end_of_macro_def(char *string);

/**
 * Function to create a new macro node for the macro list - the function allocate memory
 * @return pMacroNode a pointer to the new macro node
 */
pMacroNode create_mac_node();

/**
 * Method for inserting a macro node to the end of the macro list
 * @param mac_head the head of the macro list
 * @param string the name of the macro
 */
void insert_mac_node(pMacroNode* mac_head, char* string);

/**
 * Method for freeing all the macro nodes from the list and the memory of them all
 */
void free_macro_list();


#endif
