#ifndef ASSEMBLER_SECOND_PASS_H
#define ASSEMBLER_SECOND_PASS_H

/**
 * second_pass, a major function of the entire program. this function runs on the file for the second time, where
 * it continue to decoding some of the lines and update the data from the symbol-table to the memory image.
 * For the full algorithm of this function please look into the "Readme" file.
 * @param pFile the assembly code file
 * @param pIC the current program counter pointer - for the next free space on the memory image (start on 100)
 * @param err_flag for handling errors of all the kinds of the second pass
 */
void second_pass(FILE *pFile, int *pIC, int DC, bool *err_flag);

/**
 * Method for building one unified array for the entire memory image of the assembly file (instructions and data)
 * @param IC the final instruction counter value
 * @param DC the final data counter value
 */
void build_unified_memory_image(int IC, int DC);

#endif
