/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include <stdbool.h>
#include <string.h>

/* Function: strip

removes whitespace and comments from a line

 */
char *strip(char *s) {
    char s_new[MAX_LINE_LENGTH + 1];
    int i = 0;

    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') {
            break; // ignore comments
        }

        if (!isspace(*s2)) {
            s_new[i++] = *s2;
        }
    }
    s_new[i] = '\0';
    strcpy(s, s_new);

    return s;
}

/* Function: skip_blank_line

checks if the given line is a blank line.

 */
bool skip_blank_line(const char *line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) {
            return false;
        }
        line++;
    }
    return true;
}

/* Function: is_Atype

determines if the line represents an Atype instruction.

 */
bool is_Atype(const char *line) {
    return line[0] == '@';
}

/* Function: is_label

determines if the line represents a label.

 */
bool is_label(const char *line) {
    int len = strlen(line);
    return len > 1 && line[0] == '(' && line[len - 1] == ')';
}

/* Function: extract_label

extracts a label from a line and removes parentheses.

 */
char *extract_label(const char *line, char *label) {
    int length = strlen(line);

    // check if the line has parentheses as expected
    if (line[0] == '(' && line[length - 1] == ')') {
        strncpy(label, line + 1, length - 2); // copy without the parentheses
        label[length - 2] = '\0'; // null terminate the string
    }

    return label;
}

/* Function: is_Ctype

determines if the line represents a Ctype instruction.

 */
bool is_Ctype(const char *line) {
    return line[0] != '@' && line[0] != '(' && !skip_blank_line(line);
}

/* Function: parse

parses the input file, extracting instructions and labels.

 */
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include <stdbool.h>
#include <string.h>

void parse(FILE *file) {
    char line[256];
    unsigned int line_num = 0;  // tracks the line number
    unsigned int instr_num = 1; // start instruction number at 1

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        strip(line); // remove comments and whitespace

        if (skip_blank_line(line)) {
            continue; // skip blank lines
        }

        if (instr_num > MAX_INSTRUCTIONS) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS);
        }

        char inst_type = ' '; // default to space for unknown instruction types

        if (is_Atype(line)) {
            inst_type = 'A';
            printf("%u: %c  %s\n", instr_num, inst_type, line);
            instr_num++; // increment instruction count for A type
        } else if (is_label(line)) {
            char label[MAX_LABEL_LENGTH];
            extract_label(line, label);

            if (!isalpha(label[0])) {
                exit_program(EXIT_INVALID_LABEL, line_num, line); // use `line` for correct format
            }

            if (symtable_find(label) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line); // sse `line` for correct format
            }

            symtable_insert(label, instr_num); // label linked with the current instruction number
        } else if (is_Ctype(line)) {
            inst_type = 'C';
            printf("%u: %c  %s\n", instr_num, inst_type, line);
            instr_num++; // increment instruction count for C type
        }
    }
}
