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

typedef struct c_instruction {
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;
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
void parse(FILE * file);
bool is_Atype (const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
void add_predefined_symbols();
char *extract_label(const char *line, char *label);
bool parse_A_instruction(const char *line, a_instruction *instr);

#endif
