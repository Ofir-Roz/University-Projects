#ifndef ASSEMBLER_FILES_HANDLER_H
#define ASSEMBLER_FILES_HANDLER_H

/**
 * Method for outputting different output files: object file, entries file and externals file
 * @param file_name the name of the assembly file
 * @param finalIC the final instruction counter of the whole memory image
 */
void output_file_builder(char *file_name, int finalIC, int finalDC);

/**
 * Method for building the object file of the translated assembly file, from the memory image
 * @param fileName the name of the assembly file
 * @param finalIC the final instruction counter of the whole memory image
 */
void build_obj_file(char *fileName, int finalIC, int finalDC);

/**
 * Method for translating memory line (with memory word inside) into object file line.
 * The line contains the address of the word and the binary representation of the memory word.
 * Format:  "address\t\t binary word form"
 * @param memLine the memory line to translate
 * @param lineBuff buffer for holding the translated line
 */
void translate_memword_to_obj_line(MemoryLine memLine, char lineBuff[81]);

/**
 * Method for changing the object line into the "special base" of the program requirements.
 * '.' instead of '0' and '/' instead of '1'
 * @param post The line to modify
 */
void change_for_special_base(char post[MAX_LINE_LEN]);

/**
 * Method for building the external file, the file contains all the external labels
 * @param fileName the name of the assembly file
 */
void build_extern_file(char *fileName);

/**
 * Method for building the entries file, the file contains all the entry labels
 * @param fileName the name of the assembly file
 */
void build_entries_file(char *fileName);

/**
 * Method for posting a given string into some file
 * @param pFile pointer for the file to post the string into
 * @param string the given string to post inside the file
 */
void post_line_in_file(FILE *pFile, char *string);

/**
 * Function for getting the next line from a source file into a buffer string
 * @param pFile the source file to take the line from
 * @param pString the string buffer for holding the line
 * @return True if the line was copied successfully and is not too long, else return false
 */
bool read_next_src_line(FILE *pFile, char *pString, bool *errFlag);

/**
 * Method for updating the name of the file for the correct file path to the file
 * @param fileName the name of the file we need to work with
 * @param filePath the path buffer to fill with the updated path
 */
void update_file_path(char *fileName, char *filePath);

/**
 * Simple method for trimming the end of the file name (".as" as example), leaving the name without the ending
 * @param fileName the name of the file to modify
 */
void trim_file_name(char *fileName);

#endif
