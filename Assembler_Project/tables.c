#include "main_header.h"

extern pNode listHead;
pNode extrnList;
extern int lineNum;

void update_IC_data_in_label_table(int IC) {
    pNode curr = listHead;

    while (curr != NULL){
        if ((curr->content.type) == data)
            curr->content.value += IC;
        curr = curr->next;
    }
}

void update_entries_in_table(char *line) {
    char labelBuff[MAX_NAME_LEN];
    pNode curr = listHead;

    /* moving on to get the entry label name*/
    remove_word_from_string(line, ENTRY);
    if (is_legal_extern_entry_args(line)) {

        take_first_word_from_line(labelBuff, line);
        /* search in the symbol-table the right label to update */
        while (curr != NULL) {
            if ((!strcmp(curr->name, labelBuff)))
                curr->content.EntOrExt = entry;
            curr = curr->next;
        }
    }
}

/*
 * if there is time merge the 2 of the functions.
 */
void collect_data_label_name(int DC, char *string, int *errFlag) {
    Label newLabel;
    newLabel.type = data;
    newLabel.value = DC;
    newLabel.EntOrExt = regular;
    /* find if the same label name is already in the list */
    if (search_label_node(string, listHead)) {
        *errFlag = ON;
        print_err_or_warn("The label name is already in use.", ERROR, lineNum);
        return;
    }

    add_label_node_to_end(&listHead, string, newLabel);
}

void collect_code_label_name(int IC, char *string, bool *errFlag) {
    Label newLabel;
    newLabel.type = code;
    newLabel.value = IC;
    newLabel.EntOrExt = regular;
    /* find if the same label name is already in the list */
    if (search_label_node(string, listHead)) {
        *errFlag = ON;
        print_err_or_warn("The label name is already in use.", ERROR, lineNum);
        return;
    }

    add_label_node_to_end(&listHead, string, newLabel);
}

void insert_extern_to_table(char *string, bool *errFlag, int IC) {
    Label exeLabel;
    char labelBuff[MAX_NAME_LEN];
    exeLabel.EntOrExt = external;
    exeLabel.value = IC;

    remove_word_from_string(string, EXTERNAL);
    if (is_legal_extern_entry_args(string)) {
        /* take the .extern arg and insert it to the list */
        take_first_word_from_line(labelBuff, string);
        add_label_node_to_end(&listHead, labelBuff, exeLabel);

    } else {
        *errFlag = ON;
        print_err_or_warn("The extern args are illegal.", ERROR, lineNum);
        return;
    }
}

bool is_label_in_list(char *name) {
    pNode curr = listHead;

    while (curr != NULL){
        if (!strncmp(name, curr->name, strlen(curr->name)))
            return TRUE;
        curr = curr->next;
    }
    return FALSE;
}

/* Function to search for a label node with a given name */
pNode search_label_node(char *name, pNode head) {
    pNode current_node = head;
    while (current_node != NULL) {
        if (strcmp(current_node->name, name) == 0) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;
}

/* Function to create a new label node with a given name and data */
pNode create_label_node(char *name, Label data) {
    pNode new_node = (pNode)malloc(sizeof(LabelNode));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->name, name);
    new_node->content = data;

    if (data.EntOrExt == external)
        new_node->content.EntOrExt = external;
    else
        new_node->content.EntOrExt = regular;

    new_node->next = NULL;
    return new_node;
}

/* Function to free the memory used by the linked list */
void free_label_list(pNode head) {
    pNode current_node = head;
    while (current_node != NULL) {
        pNode next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    listHead = NULL;
}

/* Function to add a new label node to the end of the list */
void add_label_node_to_end(pNode *head, char *name, Label data) {
    pNode current_node;
    pNode new_node = create_label_node(name, data);

    if (*head == NULL) {
        *head = new_node;
    } else {
        current_node = *head;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}

bool is_there_extern_entry_in_symbol_table(const char entry_or_extern) {
    pNode currNode;
    currNode = listHead;

    switch (entry_or_extern) {

        case ENTRY_CHAR:
            while (currNode != NULL)
                if (currNode->content.EntOrExt == entry)
                    return TRUE;
                else
                    currNode = currNode->next;
            break;

        case EXTERN_CHAR:
            while (currNode != NULL)
                if (currNode->content.EntOrExt == external)
                    return TRUE;
                else
                    currNode = currNode->next;
            break;

        default:
            break;
    }

    /* external or entry not founded */
    return FALSE;
}

void add_external_operand_to_exList(pNode externalNode, int IC) {
    externalNode->content.value = IC;

    add_label_node_to_end(&extrnList, externalNode->name, externalNode->content);
}

























