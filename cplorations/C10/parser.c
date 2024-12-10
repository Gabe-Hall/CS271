#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"

/* Function: strip
 * -------------
 * Remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s) {
    char s_new[MAX_LINE_LENGTH] = {0};
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

/* Function: parse
 * -------------
 * Iterate each line in the file, strip whitespace and comments, and parse instructions.
 *
 * file: pointer to FILE to parse
 *
 * returns: number of instructions parsed
 */
int parse(FILE *file, instruction *instructions) {
    char line[MAX_LINE_LENGTH] = {0};
    int rom_address = 0;
    unsigned int line_num = 0;
    unsigned int instr_num = 0;
    add_predefined_symbols();
    instruction instr;
    char tmp_line[MAX_LINE_LENGTH] = {0};

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        if (instr_num >= MAX_INSTRUCTIONS){
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
        strip(line); // Remove comments and whitespace
        if (!*line) {
            continue; // Skip blank lines
        }
        if (is_label(line)) {
            char label[MAX_LABEL_LENGTH] = {0};
            extract_label(line, label);
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
            if (instr.instr.A_TYPE_INSTR.is_addr) {
                printf("A: %d\n", instr.instr.A_TYPE_INSTR.operand.address);
            } else {
                printf("A: %s\n", instr.instr.A_TYPE_INSTR.operand.label);
            }
            rom_address++;
        } else if (is_Ctype(line)) {
            strcpy(tmp_line, line);
            parse_C_instruction(tmp_line, &instr.instr.C_TYPE_INSTR, line_num);
            if(instr.instr.C_TYPE_INSTR.comp == COMP_INVALID) {
                exit_program(EXIT_INVALID_C_COMP, line_num, line);
            }
            else if(instr.instr.C_TYPE_INSTR.dest == DEST_INVALID) {
                exit_program(EXIT_INVALID_C_DEST, line_num, line);
            }
            else if(instr.instr.C_TYPE_INSTR.jump == JMP_INVALID) {
                exit_program(EXIT_INVALID_C_JUMP, line_num, line);
            }
            // Print the components directly as in the working code
            printf("C: d=%d, c=%d, j=%d\n",
                   instr.instr.C_TYPE_INSTR.dest,
                   instr.instr.C_TYPE_INSTR.comp,
                   instr.instr.C_TYPE_INSTR.jump);
            instr.type = C_TYPE_INSTR;
            rom_address++;
        }
        instructions[instr_num++] = instr;
    }
    return instr_num;
}

/* Function: is_Atype
 * -------------
 * Check if the instruction is an A-type
 *
 * line: the instruction line
 *
 * returns: true if A-type, false otherwise
 */
bool is_Atype(const char *line) {
    return line != NULL && line[0] == '@';
}

/* Function: is_label
 * -------------
 * Check if the line is a label
 *
 * line: the line to check
 *
 * returns: true if label, false otherwise
 */
bool is_label(const char *line) {
    return (line[0] == '(') && (line[strlen(line)-1] == ')');
}

/* Function: is_Ctype
 * -------------
 * Check if the instruction is a C-type
 *
 * line: the instruction line
 *
 * returns: true if C-type, false otherwise
 */
bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line);
}

/* Function: extract_label
 * -----------------------
 * Extract label name from a label line
 *
 * line: the label line
 * label: buffer to store the extracted label
 *
 * returns: pointer to the label
 */
char *extract_label(const char *line, char* label){
    int i = 0;
    for (const char *s = line; *s; s++){
        if (*s == '(' || *s == ')'){
            continue;
        }
        else{
            label[i++] = *s;
        }
    }
    label[i] = '\0';
    return label;
}

/* Function: add_predefined_symbols
 * -------------------------------
 * Insert predefined symbols into the symbol table
 */
void add_predefined_symbols() {
    for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
        predefined_symbol ps = predefined_symbols[i];
        symtable_insert(ps.name, ps.address);
    }
}

/* Function: parse_A_instruction
 * -----------------------------
 * Parse an A-type instruction
 *
 * line: the instruction line
 * instr: pointer to a_instruction struct to fill
 *
 * returns: true if valid, false otherwise
 */
bool parse_A_instruction(const char *line, a_instruction *instr){
    char *s = (char *)malloc(strlen(line) + 1);
    if (s == NULL) {
        return false;
    }
    strcpy(s, line + 1);
    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);
    if (s == s_end){
        instr->operand.label = strdup(s);
        if (instr->operand.label == NULL) {
            free(s);
            return false;
        }
        instr->is_addr = false;
    }
    else if (*s_end != '\0'){
        free(s);
        return false;
    }
    else{
        instr->operand.address = (int16_t)result;
        instr->is_addr = true;
    }
    free(s);
    return true;
}

/* Function: parse_C_instruction
 * -----------------------------
 * Parse a C-type instruction
 *
 * line: the instruction line
 * instr: pointer to c_instruction struct to fill
 * line_num: current line number for error reporting
 */
void parse_C_instruction(char *line, c_instruction *instr, unsigned int line_num) {
    char *temp = strtok(line, ";");
    char *jump = strtok(NULL, ";");
    char *dest = strtok(temp, "=");
    char *comp = strtok(NULL, "=");
    if (comp == NULL) {
        comp = dest;
        dest = NULL;
    }
    int a = 0;
    instr->comp = str_to_compid(comp, &a);
    instr->a = a;
    instr->jump = str_to_jumpid(jump);
    instr->dest = str_to_destid(dest);

    // Validation is handled in the parse function
}
