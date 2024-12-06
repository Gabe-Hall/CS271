#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){
    char s_new[strlen(s) + 1];
    int i = 0;
    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') {
            break; // Stop at the start of a comment
        } else if (!isspace(*s2)) {
            s_new[i++] = *s2; // Copy non-whitespace characters
        }
    }
    s_new[i] = '\0';
    strcpy(s, s_new);
    return s;
}

/* Function: parse
 * -------------
 * iterate each line in the file and process labels, A-instructions, and C-instructions.
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE *file) {
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int rom_address = 0;
    unsigned int line_num = 0;

    add_predefined_symbols();

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        strip(line); // Remove comments and whitespace
        if (!*line) {
            continue; // Skip blank lines
        }

        if (is_label(line)) {
            char label[MAX_LABEL_LENGTH] = {0};
            extract_label(line, label);
            if (!isalpha(label[0]) || symtable_find(label)) {
                exit_program(EXIT_INVALID_LABEL, line_num, label);
            }
            symtable_insert(label, rom_address);
        } else if (is_Atype(line)) {
            instruction instr;
            if (!parse_A_instruction(line, &instr.instr.a)) {
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }
            rom_address++;
        } else if (is_Ctype(line)) {
            rom_address++;
        }
    }
}

/* Function: parse_A_instruction
 * -------------
 * Parses an A-instruction and distinguishes between numbers, labels, and errors.
 */
bool parse_A_instruction(const char *line, a_instruction *instr) {
    char *s = malloc(strlen(line));
    strcpy(s, line + 1); // Skip '@'
    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if (s == s_end) { // Not a number, must be a label
        if (!isalpha(s[0])) { // Labels must start with an alphabetic character
            free(s);
            return false;
        }
        instr->operand.label = strdup(s);
        instr->is_addr = false;
    } else if (*s_end != '\0') { // Invalid label (contains non-numeric characters)
        free(s);
        return false;
    } else {
        instr->operand.address = (int16_t)result;
        instr->is_addr = true;
    }
    free(s);
    return true;
}

/* Additional helper functions */
bool is_Atype(const char *line) {
    return line[0] == '@';
}

bool is_label(const char *line) {
    return line[0] == '(' && line[strlen(line) - 1] == ')';
}

bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line);
}

char *extract_label(const char *line, char *label) {
    int i = 0;
    for (const char *s = line; *s; s++) {
        if (*s != '(' && *s != ')') {
            label[i++] = *s;
        }
    }
    label[i] = '\0';
    return label;
}

void add_predefined_symbols() {
    for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
        symtable_insert(predefined_symbols[i].name, predefined_symbols[i].address);
    }
}
