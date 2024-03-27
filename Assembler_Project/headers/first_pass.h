#ifndef ASSEMBLER_FIRST_PASS_H
#define ASSEMBLER_FIRST_PASS_H

/**
 * first_pass, a major function of the entire program. this function runs on the file for the first time, where
 * it start to decoding some of the lines and upload data into the symbol-table and the memory image.
 * For the full algorithm of this function please look into the "Readme" file.
 * @param pFile the file to read the lines from
 * @param pIC the current program counter pointer - for the next free space on the memory image (start on 100)
 * @param pDC the current instruction counter pointer - for the next free data space on the memory image
 * @param err_flag for handling errors of all the kinds of the first pass
 */
void first_pass(FILE *pFile, int *pIC, int *pDC, bool *err_flag);

#endif
