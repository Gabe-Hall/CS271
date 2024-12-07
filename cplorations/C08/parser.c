<<<<<<< HEAD
/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Gabriel Hall
 * [TERM] FALL 2024
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include <string.h>
#include <ctype.h>

/* Removes comments and whitespace from a line */
char *strip(char *s) {
    char s_new[MAX_LINE_LENGTH + 1];
    int i = 0;
    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') break;  // Ignore comments
        if (!isspace(*s2)) s_new[i++] = *s2;
    }
    s_new[i] = '\0';
    strcpy(s, s_new);
    return s;
}

/* Parse the input file */
void parse(FILE *file) {
    char line[MAX_LINE_LENGTH] = {0};
    char label[MAX_LABEL_LENGTH] = {0};
    unsigned int line_num = 0;
    unsigned int rom_address = 0;
    unsigned int instr_num = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        strip(line);
        if (!*line) continue;

        char inst_type = ' ';
        if (is_Atype(line)) {
            inst_type = 'A';
        } else if (is_Ctype(line)) {
            inst_type = 'C';
        } else if (is_label(line)) {
            extract_label(line, label);
            if (!isalpha(label[0])) {
                exit_program(EXIT_INVALID_LABEL, line_num, label);
            }
            if (symtable_find(label) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
            }
            symtable_insert(label, rom_address);
            continue;
        } else {
            continue;
        }

        printf("%u: %c  %s\n", rom_address, inst_type, line);
        instr_num++;
        rom_address++;

        if (instr_num > MAX_INSTRUCTIONS) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
    }
}

/* Determines if a line is an A-type instruction */
bool is_Atype(const char *line) {
    return line[0] == '@';
}

/* Determines if a line is a label */
bool is_label(const char *line) {
    size_t len = strlen(line);
    return len > 1 && line[0] == '(' && line[len - 1] == ')';
}

/* Determines if a line is a C-type instruction */
bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line);
}

/* Extracts the label from a line */
char *extract_label(const char *line, char *label) {
    size_t len = strlen(line) - 2;
    strncpy(label, line + 1, len);
    label[len] = '\0';
    return label;
}
=======
/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Gabriel Hall
 * [TERM] FALL 2024
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include <string.h>
#include <ctype.h>

/* Removes comments and whitespace from a line */
char *strip(char *s) {
    char s_new[MAX_LINE_LENGTH + 1];
    int i = 0;
    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') break;  // Ignore comments
        if (!isspace(*s2)) s_new[i++] = *s2;
    }
    s_new[i] = '\0';
    strcpy(s, s_new);
    return s;
}

/* Parse the input file */
void parse(FILE *file) {
    char line[MAX_LINE_LENGTH] = {0};
    char label[MAX_LABEL_LENGTH] = {0};
    unsigned int line_num = 0;
    unsigned int rom_address = 0;
    unsigned int instr_num = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        strip(line);
        if (!*line) continue;

        char inst_type = ' ';
        if (is_Atype(line)) {
            inst_type = 'A';
        } else if (is_Ctype(line)) {
            inst_type = 'C';
        } else if (is_label(line)) {
            extract_label(line, label);
            if (!isalpha(label[0])) {
                exit_program(EXIT_INVALID_LABEL, line_num, label);
            }
            if (symtable_find(label) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
            }
            symtable_insert(label, rom_address);
            continue;
        } else {
            continue;
        }

        printf("%u: %c  %s\n", rom_address, inst_type, line);
        instr_num++;
        rom_address++;

        if (instr_num > MAX_INSTRUCTIONS) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
    }
}

/* Determines if a line is an A-type instruction */
bool is_Atype(const char *line) {
    return line[0] == '@';
}

/* Determines if a line is a label */
bool is_label(const char *line) {
    size_t len = strlen(line);
    return len > 1 && line[0] == '(' && line[len - 1] == ')';
}

/* Determines if a line is a C-type instruction */
bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line);
}

/* Extracts the label from a line */
char *extract_label(const char *line, char *label) {
    size_t len = strlen(line) - 2;
    strncpy(label, line + 1, len);
    label[len] = '\0';
    return label;
}
>>>>>>> 5543e7c8b71009152f6be1640862c34671550079
