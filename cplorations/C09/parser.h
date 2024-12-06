#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <stdbool.h>
#include "hack.h"

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

typedef struct a_instruction {
    union {
        int16_t address;
        char *label;
    } operand;
    bool is_addr;
} a_instruction;

typedef struct instruction {
    union {
        a_instruction a;
    } instr;
} instruction;

void parse(FILE *file);
bool parse_A_instruction(const char *line, a_instruction *instr);
void add_predefined_symbols();
bool is_Atype(const char *line);
bool is_label(const char *line);
char *extract_label(const char *line, char *label);
char *strip(char *line);

#endif
