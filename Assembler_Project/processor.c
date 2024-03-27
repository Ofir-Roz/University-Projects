#include "main_header.h"

#define NAME_COLLECTION 'n'
#define DATA_COLLECTION 'd'

extern int lineNum;
pMacroNode macHead = NULL;     /* Macro list head */
pNode listHead;               /* linked list head */

void pre_processor(char *file_name, char *am_ending_name)
{
    FILE *p_src, *p_new;
    char line_buff[MAX_LINE_LEN], macro_name[MAX_NAME_LEN];
    char src_path[MAX_PATH_LENGTH], new_path[MAX_PATH_LENGTH];
    bool macro_flag = FALSE;
    lineNum = 0;

    update_file_path(file_name, src_path);
    update_file_path(am_ending_name, new_path);
    p_src = fopen(src_path, "r");
    p_new = fopen(new_path, "w+");

    if (p_src == NULL || p_new == NULL) 
        print_err_N_exit("No files to work with inside the directory", -999);

    while (read_next_src_line(p_src, line_buff, 0))
    {
        strcpy(line_buff, eliminate_left_whites(line_buff));
        lineNum++;

        if (is_macro_name_detected(line_buff))
        {
            extract_macro_name(line_buff, macro_name);
            deploy_macro_content_in_file(p_new, macro_name);
        }
        else
        {
            if (is_new_macro_ahead(line_buff) || macro_flag)
            {
                if (macro_flag)
                    collect_macro(line_buff, DATA_COLLECTION, macro_name);
                else {
                    macro_flag = TRUE;
                    remove_word_from_string(line_buff, "mcr");
                    extract_macro_name(line_buff, macro_name);
                    collect_macro(line_buff, NAME_COLLECTION, macro_name);
                }
            }

            if (!macro_flag) {
                if (line_buff[0] != '\0')
                    post_line_in_file(p_new, line_buff);
            }
            else
            {

                read_next_src_line(p_src, line_buff, 0);
                strcpy(line_buff, eliminate_left_whites(line_buff));
                lineNum++;

                if (is_end_of_macro_def(line_buff))
                    macro_flag = FALSE;
                else
                    collect_macro(line_buff, DATA_COLLECTION, macro_name);

            }
        }
    }

    fclose(p_src);
    fclose(p_new);
    free_macro_list();
    macHead = NULL;
}

void code_processor(char *file_name, bool *err_flag)
{
    int IC ,DC ;
    FILE *p_src;

    p_src = fopen(file_name, "r");

    first_pass(p_src, &IC, &DC, err_flag);

    if(err_flag == ON)
        print_err_or_warn("The file has some errors, therefor there is no output files", ERROR, 0);
    else
        output_file_builder(file_name, IC, DC);

    fclose(p_src);
}


/*
 *
 * assistance part.
 *
 * */

char *extract_macro_name(const char *string, char *name) {
    size_t len;
    const char *q;
    const char *p = string;

    while (isspace(*p)) {
        p++;
    }
    q = p;
    while (*q && !isspace(*q)) {
        q++;
    }
    len = q - p;
    strncpy(name, p, len);
    name[len] = '\0';

    return name;
}

void collect_macro(char *string, char name_or_data, char *mac_name) {

    switch (name_or_data) {
        case NAME_COLLECTION:
            extract_macro_name(string, mac_name);
            collect_new_macro_name(mac_name);
            break;

        case DATA_COLLECTION:
            collect_macro_content(mac_name, string);
            break;

        default:
            break;
    }
}

void collect_new_macro_name(char *string) {

    if(!is_mac_name_exist_in_list(string)) {
        insert_mac_node(&macHead, string);
    } else
        print_err_N_exit("Macro name already exist. exit.", lineNum);
}


void collect_macro_content(const char *name, char *content) {
    pMacroNode current = macHead;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {

            if (current->content == NULL) {
                current->content = (char *) malloc(sizeof(char) * strlen(content));
                if (current->content == NULL) {
                    printf("Error: Memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
            }
            else {
                current->content = realloc(current->content, strlen(current->content) + strlen(content) + 1);
                if (current->content == NULL) {
                    printf("Error: Memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
            }

            strcat(current->content, content);
            /* strcat(current->content, "\n"); */
            return;
        }
        current = current->next;
    }

    print_err_N_exit("Macro name not exist.", lineNum);
}

void deploy_macro_content_in_file(FILE *pFile, char *name) {
    char *c;
    pMacroNode current = macHead;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {

            while ((c = strchr(current->content, '\r')))
                *c = '\n';

            fprintf(pFile, "%s", current->content);
            return;
        }
        current = current->next;
    }

    print_err_N_exit("Macro name not founded in the list.", lineNum);
}

bool is_new_macro_ahead(char *string) {
    return !strncmp(string, "mcr", 3) ? TRUE : FALSE;
}

bool is_macro_name_detected(char *string) {
    pMacroNode curr = macHead;

    while (curr != NULL){
        if (!strncmp(string, curr->name, strlen(curr->name)))
            return TRUE;
        curr = curr->next;
    }
    return FALSE;
}

bool is_mac_name_exist_in_list(char *string) {
    pMacroNode current = macHead;
    while (current != NULL && !strcmp(current->name, string)) {
        current = current->next;
    }

    return current != NULL;
}

bool is_end_of_macro_def(char *string) {
    return !strncmp(string, "endmcr", 6) ? TRUE : FALSE;
}

pMacroNode create_mac_node() {
    pMacroNode newNode = (pMacroNode)malloc(sizeof(MacroNode));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->content = NULL;
    newNode->next = NULL;
    return newNode;
}

void insert_mac_node(pMacroNode* mac_head, char* string) {
    pMacroNode current;
    pMacroNode newNode = create_mac_node();

    strcpy(newNode->name, string);

    if (*mac_head == NULL) {
        *mac_head = newNode;
        return;
    }

    current = *mac_head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void free_macro_list() {
    pMacroNode currentNode = macHead;
    while (currentNode != NULL) {
        pMacroNode next_node = currentNode->next;
        free(currentNode->content);
        free(currentNode);
        currentNode = next_node;
    }
}

































