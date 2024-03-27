#ifndef ASSEMBLER_TABLES_H
#define ASSEMBLER_TABLES_H

#define ENTRY_CHAR 'n'
#define EXTERN_CHAR 'x'

/* For the memWord of symbol that is saved in the symbol table*/
typedef enum symtype{code = 1, data} SymbolType;

/* For classify if a symbol is external or an entry */
typedef enum symentext{entry = 3, external, regular} SymbolEntExt;

/* Label is a struct that holds the data in the symbol table.
   The value member represents the  value of the memory address of the symbol.
   The memWord member is holding the memWord of the symbol (code, data, external, entry).
 */
typedef struct {
    int value;
    SymbolType type;
    SymbolEntExt EntOrExt;
} Label;

/* LabelNode is the building block of the symbol table structure that holds the symbols and the macros in linked list */
typedef struct sym_node * pNode;
typedef struct sym_node {
    char name[MAX_NAME_LEN];
    Label content;
    pNode next;
} LabelNode;

/**
 * Method for updating the entry labels on the symbol table. the labels to update are given
 * on the argument part of the line.
 * @param line the ".entry" line from the assembly file
 */
void update_entries_in_table(char *line);

/**
 * Method for updating the label list components with the last instruction counter value -
 * after the first pass (to create the separation between the code section and the data section)
 * @param IC the final instruction counter value
 * @param DC the data counter value
 */
void update_IC_data_in_label_table(int IC);

/**
 * Function for checking if the given label is exist in the label list
 * @param name the label name
 * @return TRUE if the label exist in the list
 */
bool is_label_in_list(char *name);

/**
 * Method for inserting new data label by name into the labels table list
 * @param DC the value of the label - data counter
 * @param string the label name
 * @param errFlag handling errors - if the name is already in use
 */
void collect_data_label_name(int DC, char *string, bool *errFlag);

/**
 * Method for inserting new code (commands/operations) label by name into the labels table list
 * @param IC the value of the label - instruction counter
 * @param string the label name
 * @param err_flag handling errors - if the name is already in use
 */
void collect_code_label_name(int IC, char *string, bool *err_flag);

/**
 * Method for inserting externals labels (as an arguments of ".extern") into the labels table list
 * @param string the ".extern" line with the arguments
 * @param errFlag handling errors - if the arguments are illegal
 */
void insert_extern_to_table(char *string, bool *err_flag, int IC);

/**
 * Function to search for a label node in the list with a given name
 * @param name the label
 * @param head the head of the label table
 * @return pNode pointer to the node. Null if there is no such node
 */
pNode search_label_node(char *name, pNode head);

/**
 * Function to create a new label node with a given name and data
 * @param name the label
 * @param data the label data
 * @return pNode pointer to the new created node
 */
pNode create_label_node(char *name, Label data);

/**
 * Method for releasing the label list from the memory
 * @param head the head of the list to release
 */
void free_label_list(pNode head);

/**
 * Method to add a new label node to the end of the label list
 * @param head the head of the list
 * @param name the label
 * @param data the label data
 */
void add_label_node_to_end(pNode *head, char *name, Label data);

/**
 * Function to fined if there is extern or entry nodes on the symbol table
 * @param entry_or_extern char to indicate what to search - 'n' for entry, 'x' for extern
 * @return True if there is some entry or extern nodes on the symbol table
 */
bool is_there_extern_entry_in_symbol_table(const char entry_or_extern);

/**
 * Method for adding one external value to the external list
 * @param externalNode the external node to modify and pass on
 * @param IC the instruction counter - equals to the external symbol value
 */
void add_external_operand_to_exList(pNode externalNode, int IC);

#endif