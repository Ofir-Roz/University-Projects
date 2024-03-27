#include "main_header.h"

/**
 * The main algorithm function of the program. This function initiate all of the process of the assembly file
 * decoding for each file name the user put on the command prompt. The function calls to the pre processor, then
 * to the main processor stage (the 2 runs on the file), and in the end if everything on the file is right -
 * the function calls to the output file builder process
 * @param file_name the name of the assembly source file
 */
void assembler_init(char *file_name);

/* Project Main:
 * Reading the files from the terminal, if there is instructions
 * the main add '.as' to the end of the file name;
 * call to assemblerInit for each file.
 * */

int main(int argc, char *argv[])
{
    char *file_name;

    if (argc==1) {
        printf("\nNo arguments, there is only the program name.\n");
        return 0;
    }
    else {
        printf("\n   ********************************************\n"
               "\tWelcome to the Assembler program\n\tMade by Ofir Rozanes"
               "\n   ********************************************");
        while (--argc) {
            file_name = file_ending_adder(*++argv); /* adding '.as' to the file name*/
            printf("\n------> Working on the next file:\n------> %s\n\n",file_name);
            assembler_init(file_name);
            free(file_name);
        }
    }
    return 0;
}


void assembler_init(char *file_name)
{
    bool err_flag = OFF;                                              /* flag to indicate if there is error in the file */
    char *am_ending_name = (char *)malloc(strlen(file_name));
	
    am_ending_name[0] = '\0';
    strncat(am_ending_name, file_name, (strlen(file_name) - 3));
    strcat(am_ending_name,".am");

    pre_processor(file_name, am_ending_name);

    code_processor(am_ending_name, &err_flag);
    
    free(am_ending_name);
    printf("\n____FINISH____\n");
}
