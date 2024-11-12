/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 *
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

typedef int16_t hack_addr;
typedef int16_t opcode;

typedef enum instr_type {
    INVALID = -1,
    A_TYPE,
    C_TYPE
} instr_type;
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
    };
    bool is_addr;
} a_instruction;
typedef struct instruction {
    union {
        a_instruction a_instr;
    };
    instr_type type;
} instruction;




bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
bool skip_blank_line(const char *line);

#endif


/** function prototypes **/
char *strip(char *s);
void parse(FILE * file);
char *extract_label(const char *line, char *label);
