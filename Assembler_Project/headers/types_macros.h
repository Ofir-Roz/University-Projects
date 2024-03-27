#ifndef ASSEMBLER_TYPES_MACROS_H
#define ASSEMBLER_TYPES_MACROS_H

typedef int bool;
#define TRUE 1
#define FALSE 0
#define OFF 1
#define ON 0

/* some actions on the memory words */
#define SET_BIT(WORD, PLACE) (WORD) |= ((MemoryWord)0x01 << (PLACE))
#define SET_COMMAND(WORD, PLACE) (WORD) |= ((MemoryWord)0x01 << (PLACE))
#define CLR_BIT(WORD, PLACE) (WORD) &= ~((MemoryWord)0x01 << (PLACE))
#define CLR_ALL_BITS(WORD) (WORD) = 0
#define IS_BIT_SET(WORD, PLACE) (((WORD) >> (PLACE)) & 0x01)

#define ERROR (-1)
#define WARNING 1
#define RED_COLOR "\x1b[31m"
#define MAGENTA "\x1b[35m"
#define RESET "\x1b[0m"
#define MAX_LINE_LEN 81
#define MAX_NAME_LEN 31
#define MAX_PATH_LENGTH 256
#define WORD_BUFF_LEN 10
#define ASCII_BUFF_LEN 75
#define ARGS_BUFF_LEN 77

#define BITS_LENGTH 14
#define MEMORY_SIZE 256
#define FIRST_MEMORY_PLACE 100

/* struct for the first memory memWord */
typedef struct {
    unsigned short A_R_E:2;
    unsigned short trg_op:2;
    unsigned short src_op:2;
    unsigned short opcode:4;
    unsigned short sec_parm:2;
    unsigned short frs_parm:2;
} FirstMemWord;

/* struct for the standard additional memory memWord */
typedef struct {
    unsigned short A_R_E:2;
    unsigned short content:12;
} AddiMemWord;

/* struct for the target register memory memWord */
typedef struct {
    unsigned short A_R_E:2;
    unsigned short content:6;
    unsigned short space:6;
} TarRegMemWord;

/* struct for the source register memory memWord */
typedef struct {
    unsigned short A_R_E:2;
    unsigned short space:6;
    unsigned short content:6;
} SrcRegMemWord;

/* struct for the combined registers memory memWord */
typedef struct {
    unsigned short A_R_E:2;
    unsigned short tar_content:6;
    unsigned short src_content:6;
} DoubleRegMemWord;

/* struct for the data memWord memory memWord */
typedef struct {
    short data:14;
}DataWord;


/* structs for the command memWord memory memWord and image */
typedef enum  {frsWord, addiWord, tarWord, srcWord, combWord} cmdTypeNum;
typedef struct {
    union {
        FirstMemWord frsWord;
        AddiMemWord addiWord;
        TarRegMemWord tarRegWord;
        SrcRegMemWord srcRegWord;
        DoubleRegMemWord combRegWord;
    } word;
    cmdTypeNum typeNum;
} CmdWord;

/* the basic block for the entire memory image.
 * for each kind of different coding method of single memory memWord. */
typedef struct {
    union {
        FirstMemWord frsWord;
        AddiMemWord addiWord;
        TarRegMemWord tarRegWord;
        SrcRegMemWord srcRegWord;
        DoubleRegMemWord combRegWord;
        DataWord dataWord;
    } wordType;
} MemWord;

typedef struct {
    CmdWord memWord;
    bool empty;         /* true if the memWord is empty */
} CmdLine;

/* struct for the lines of the memory image */
typedef enum {dataType, cmdType} memLineType;
typedef struct {
    int address;           /* 0-255*/
    DataWord dataWord;
    CmdWord cmdWord;
    memLineType memType;
} MemoryLine;

/* register code */
typedef enum  {r0, r1, r2, r3, r4, r5, r6, r7} regNum;

#define REG_0 "r0"
#define REG_1 "r1"
#define REG_2 "r2"
#define REG_3 "r3"
#define REG_4 "r4"
#define REG_5 "r5"
#define REG_6 "r6"
#define REG_7 "r7"

/* commands op code */
typedef enum  {MOV, CMP, ADD, SUB, NOT, CLR, LEA, INC, DEC, JMP, BNE,
                RED, PRN, JSR, RTS, STOP } cmdOpCode;

#define MOV_W "mov"
#define CMP_W "cmp"
#define ADD_W "add"
#define SUB_W "sub"
#define NOT_W "not"
#define CLR_W "clr"
#define LEA_W "lea"
#define INC_W "inc"
#define DEC_W "dec"
#define JMP_W "jmp"
#define BNE_W "bne"
#define RED_W "red"
#define PRN_W "prn"
#define JSR_W "jsr"
#define RTS_W "rts"
#define STOP_W "stop"

/* A/R/E attributes */
#define ABSOLUTE_A 0
#define EXTERNAL_A 1
#define RELOCATABLE_A 2

/* addressing methods */
#define IMMEDIATE_METHOD 0
#define DIRECT_METHOD 1
#define JMP_WITH_PARAM_METHOD 2
#define REGISTER_METHOD 3

/* bits 10-13 of the memory memWord codings */
#define IMMEDIATE_PARM 0
#define REGISTER_PARM 3 /* 11 in binary */
#define TICKET_PARM 1   /* 01 in binary */

#define DATA ".data"
#define STRING ".string"
#define ENTRY ".entry"
#define EXTERNAL ".extern"

#define SRC_REGISTER_TYPE 1
#define TAR_REGISTER_TYPE 2
#define COMB_REGISTER_TYPE 3

#endif
