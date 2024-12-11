#ifndef __HACK_H__
#define __HACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#define NUM_PREDEFINED_SYMBOLS 23

enum symbol_id {
    SYM_SP = 0,
    SYM_LCL = 1,
    SYM_ARG = 2,
    SYM_THIS = 3,
    SYM_THAT = 4,
    SYM_R0 = 0,
    SYM_R1 = 1,
    SYM_R2 = 2,
    SYM_R3 = 3,
    SYM_R4 = 4,
    SYM_R5 = 5,
    SYM_R6 = 6,
    SYM_R7 = 7,
    SYM_R8 = 8,
    SYM_R9 = 9,
    SYM_R10 = 10,
    SYM_R11 = 11,
    SYM_R12 = 12,
    SYM_R13 = 13,
    SYM_R14 = 14,
    SYM_R15 = 15,
    SYM_SCREEN = 16384,
    SYM_KBD = 24576
};

typedef struct predefined_symbol {
    char name[20];
    int16_t address;
} predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"R0", SYM_R0},
    {"R1", SYM_R1},
    {"R2", SYM_R2},
    {"R3", SYM_R3},
    {"R4", SYM_R4},
    {"R5", SYM_R5},
    {"R6", SYM_R6},
    {"R7", SYM_R7},
    {"R8", SYM_R8},
    {"R9", SYM_R9},
    {"R10", SYM_R10},
    {"R11", SYM_R11},
    {"R12", SYM_R12},
    {"R13", SYM_R13},
    {"R14", SYM_R14},
    {"R15", SYM_R15},
    {"SP", SYM_SP},
    {"LCL", SYM_LCL},
    {"ARG", SYM_ARG},
    {"THIS", SYM_THIS},
    {"THAT", SYM_THAT},
    {"SCREEN", SYM_SCREEN},
    {"KBD", SYM_KBD}
};

// Enum for Jump
typedef enum {
    JMP_INVALID = -1,
    JMP_NULL = 0,
    JMP_JGT,
    JMP_JEQ,
    JMP_JGE,
    JMP_JLT,
    JMP_JNE,
    JMP_JLE,
    JMP_JMP
} jump_id;

// Enum for Destination
typedef enum {
    DEST_INVALID = -1,
    DEST_NULL = 0,
    DEST_M,
    DEST_D,
    DEST_MD,
    DEST_A,
    DEST_AM,
    DEST_AD,
    DEST_AMD
} dest_id;

// Enum for Computation
typedef enum {
    COMP_INVALID = -1,
    COMP_0 = 42,          // 0101010
    COMP_1 = 63,          // 0111111
    COMP_MINUS_1 = 58,    // 0111010
    COMP_D = 12,          // 0001100
    COMP_A = 48,          // 0110000
    COMP_NOT_D = 13,      // 0001101
    COMP_NOT_A = 49,      // 0110001
    COMP_MINUS_D = 15,    // 0001111
    COMP_MINUS_A = 51,    // 0110011
    COMP_D_PLUS_1 = 31,   // 0011111
    COMP_A_PLUS_1 = 55,   // 0110111
    COMP_D_MINUS_1 = 14,  // 0001110
    COMP_A_MINUS_1 = 50,  // 0110010
    COMP_D_PLUS_A = 2,    // 0000010
    COMP_D_MINUS_A = 19,  // 0010011
    COMP_A_MINUS_D = 7,   // 0000111
    COMP_D_AND_A = 0,     // 0000000
    COMP_D_OR_A = 21      // 0010101
} comp_id;

// Function to map string to jump_id
static inline jump_id str_to_jumpid(const char *s) {
    jump_id id = JMP_INVALID;
    if (s == NULL) {
        id = JMP_NULL;
    } else if (strcmp(s, "JGT") == 0) {
        id = JMP_JGT;
    } else if (strcmp(s, "JEQ") == 0) {
        id = JMP_JEQ;
    } else if (strcmp(s, "JGE") == 0) {
        id = JMP_JGE;
    } else if (strcmp(s, "JLT") == 0) {
        id = JMP_JLT;
    } else if (strcmp(s, "JNE") == 0) {
        id = JMP_JNE;
    } else if (strcmp(s, "JLE") == 0) {
        id = JMP_JLE;
    } else if (strcmp(s, "JMP") == 0) {
        id = JMP_JMP;
    }
    return id;
}

// Function to map string to dest_id
static inline dest_id str_to_destid(const char *s) {
    dest_id id = DEST_INVALID;
    if (s == NULL) {
        id = DEST_NULL;
    } else if (strcmp(s, "M") == 0) {
        id = DEST_M;
    } else if (strcmp(s, "D") == 0) {
        id = DEST_D;
    } else if (strcmp(s, "MD") == 0) {
        id = DEST_MD;
    } else if (strcmp(s, "A") == 0) {
        id = DEST_A;
    } else if (strcmp(s, "AM") == 0) {
        id = DEST_AM;
    } else if (strcmp(s, "AD") == 0) {
        id = DEST_AD;
    } else if (strcmp(s, "AMD") == 0) {
        id = DEST_AMD;
    }
    return id;
}

// Function to map string to comp_id
static inline comp_id str_to_compid(const char *s, int *a) {
    comp_id id = COMP_INVALID;
    *a = 0; // Default 'a' bit to 0

    if (s == NULL) {
        return id;
    }

    if (strcmp(s, "0") == 0) {
        id = COMP_0;
    } else if (strcmp(s, "1") == 0) {
        id = COMP_1;
    } else if (strcmp(s, "-1") == 0) {
        id = COMP_MINUS_1;
    } else if (strcmp(s, "D") == 0) {
        id = COMP_D;
    } else if (strcmp(s, "A") == 0) {
        id = COMP_A;
    } else if (strcmp(s, "!D") == 0) {
        id = COMP_NOT_D;
    } else if (strcmp(s, "!A") == 0) {
        id = COMP_NOT_A;
    } else if (strcmp(s, "-D") == 0) {
        id = COMP_MINUS_D;
    } else if (strcmp(s, "-A") == 0) {
        id = COMP_MINUS_A;
    } else if (strcmp(s, "D+1") == 0) {
        id = COMP_D_PLUS_1;
    } else if (strcmp(s, "A+1") == 0) {
        id = COMP_A_PLUS_1;
    } else if (strcmp(s, "D-1") == 0) {
        id = COMP_D_MINUS_1;
    } else if (strcmp(s, "A-1") == 0) {
        id = COMP_A_MINUS_1;
    } else if (strcmp(s, "D+A") == 0) {
        id = COMP_D_PLUS_A;
    } else if (strcmp(s, "D-M") == 0) {
        id = COMP_D_MINUS_A;
    } else if (strcmp(s, "M-D") == 0) {
        id = COMP_A_MINUS_D;
        *a = 1;
    } else if (strcmp(s, "D&M") == 0) {
        id = COMP_D_AND_A;
        *a = 1;
    } else if (strcmp(s, "D|A") == 0) {
        id = COMP_D_OR_A;
    }
    // Handle M-based computations by mapping to A-based comp_id and setting 'a' bit
    else if (strcmp(s, "M") == 0) {
        id = COMP_A;
        *a = 1;
    } else if (strcmp(s, "!M") == 0) {
        id = COMP_NOT_A;
        *a = 1;
    } else if (strcmp(s, "-M") == 0) {
        id = COMP_MINUS_A;
        *a = 1;
    } else if (strcmp(s, "M+1") == 0) {
        id = COMP_A_PLUS_1;
        *a = 1;
    } else if (strcmp(s, "M-1") == 0) {
        id = COMP_A_MINUS_1;
        *a = 1;
    } else if (strcmp(s, "D+M") == 0) {
        id = COMP_D_PLUS_A;
        *a = 1;
    } else if (strcmp(s, "D-M") == 0) {
        id = COMP_D_MINUS_A;
        *a = 1;
    } else if (strcmp(s, "M-D") == 0) {
        id = COMP_A_MINUS_D;
        *a = 1;
    } else if (strcmp(s, "D&M") == 0) {
        id = COMP_D_AND_A;
        *a = 1;
    } else if (strcmp(s, "D|M") == 0) {
        id = COMP_D_OR_A;
        *a = 1;
    }

    return id;
}

#define OPCODE_TO_BINARY(opcode) \
    ((opcode & 0x8000) ? '1' : '0'), \
    ((opcode & 0x4000) ? '1' : '0'), \
    ((opcode & 0x2000) ? '1' : '0'), \
    ((opcode & 0x1000) ? '1' : '0'), \
    ((opcode & 0x0800) ? '1' : '0'), \
    ((opcode & 0x0400) ? '1' : '0'), \
    ((opcode & 0x0200) ? '1' : '0'), \
    ((opcode & 0x0100) ? '1' : '0'), \
    ((opcode & 0x0080) ? '1' : '0'), \
    ((opcode & 0x0040) ? '1' : '0'), \
    ((opcode & 0x0020) ? '1' : '0'), \
    ((opcode & 0x0010) ? '1' : '0'), \
    ((opcode & 0x0008) ? '1' : '0'), \
    ((opcode & 0x0004) ? '1' : '0'), \
    ((opcode & 0x0002) ? '1' : '0'), \
    ((opcode & 0x0001) ? '1' : '0')

#endif // __HACK_H__
