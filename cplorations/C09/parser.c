#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"

char *strip(char *s){
    char s_new[strlen(s) + 1];
    int i = 0;
    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') {
            break;
        } else if (!isspace((unsigned char)*s2)) {
            s_new[i++] = *s2;
        }
    }
    s_new[i] = '\0';
    strcpy(s, s_new);
    return s;
}

void parse(FILE *file) {
    char line[MAX_LINE_LENGTH] = {0};
    int rom_address = 0;
    unsigned int line_num = 0;
    unsigned int instr_num = 0;
    add_predefined_symbols();
    instruction instr;

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        if (instr_num > MAX_INSTRUCTIONS) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
        strip(line);
        if (!*line) {
            continue; // Skip blank lines
        }

        if (is_label(line)) {
            char label[MAX_LABEL_LENGTH] = {0};
            strcpy(line, extract_label(line, label));
            if (!isalpha((unsigned char)label[0])) {
                exit_program(EXIT_INVALID_LABEL, line_num, label);
            }
            if (symtable_find(label) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
            }
            symtable_insert(label, rom_address);
        } else if (is_Atype(line)) {
            if (!parse_A_instruction(line, &instr.instr.A_TYPE_INSTR)) {
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }
            instr.type = A_TYPE_INSTR;
            rom_address++;
        } else if (is_Ctype(line)) {
            instr.type = C_TYPE_INSTR;
            rom_address++;
        }
        instr_num++;
    }
}

bool is_Atype(const char *line) {
    return line != NULL && line[0] == '@';
}

bool is_label(const char *line) {
    return (line[0] == '(' && line[strlen(line)-1] == ')');
}

bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line);
}

char *extract_label(const char *line, char *label) {
    int i = 0;
    for (const char *s = line; *s; s++){
        if (*s == '(' || *s == ')') {
            continue;
        } else {
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

bool parse_A_instruction(const char *line, a_instruction *instr) {
    char *s = (char *)malloc(strlen(line) + 1);
    if (!s) return false;
    strcpy(s, line + 1);

    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);
    if (s == s_end) {
        instr->operand.label = (char *)malloc(strlen(s) + 1);
        if (!instr->operand.label) {
            free(s);
            return false;
        }
        strcpy(instr->operand.label, s);
        instr->is_addr = false;
    } else if (*s_end != '\0') {
        free(s);
        return false;
    } else {
        instr->operand.address = (int16_t)result;
        instr->is_addr = true;
    }

    free(s);
    return true;
}
