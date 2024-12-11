#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "symtable.h"
#include "error.h"
#include "hack.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type {
    INVALID_INSTR = -1,
    A_TYPE_INSTR,
    C_TYPE_INSTR,
    L_TYPE_INSTR
};

// Reordered bitfields: comp first, then a
typedef struct c_instruction {
    opcode comp:7;  // Computation bits (c1-c7)
    opcode a:1;     // a bit (c8)
    opcode dest:4;  // Destination bits (d1-d4)
    opcode jump:4;  // Jump bits (j1-j4)
} c_instruction;

typedef struct a_instruction {
    union {
        hack_addr address;
        char *label;
    } operand;
    bool is_addr;
} a_instruction;

typedef struct instruction {
    union {
        a_instruction A_TYPE_INSTR;
        c_instruction C_TYPE_INSTR;
    } instr;
    enum instr_type type;
} instruction;

char *strip(char *s);
int parse(FILE *file, instruction *instructions);
bool is_Atype (const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
void add_predefined_symbols();
char *extract_label(const char *line, char *label);
bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr, unsigned int line_num);

// New function declarations
void assemble(const char *file_name, instruction* instructions, int num_instructions);
opcode instruction_to_opcode(c_instruction instr);

#endif // __PARSER_H__
