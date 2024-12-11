#include "parser.h"

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

// New function implementations below

/* Function: instruction_to_opcode
 * -------------------------------
 * Convert a C-instruction struct to its binary opcode
 *
 * instr: the C-instruction to convert
 *
 * returns: the binary opcode as an int16_t
 */
opcode instruction_to_opcode(c_instruction instr) {
    opcode op = 0;
    op |= (7 << 13); // Set the first three bits to '111'

    op |= (instr.a << 12); // Set the 'a' bit

    op |= (instr.comp << 6); // Set the 'comp' bits

    op |= (instr.dest << 3); // Set the 'dest' bits

    op |= (instr.jump);      // Set the 'jump' bits

    return op;
}

/* Function: opcode_to_binary_string
 * ---------------------------------
 * Convert opcode to a binary string using OPCODE_TO_BINARY macro
 *
 * opcode: the binary opcode
 * binary_str: buffer to store the binary string
 */
void opcode_to_binary_string(int opcode, char *binary_str) {
    // Expand the OPCODE_TO_BINARY macro into individual bits
    char bits[] = {OPCODE_TO_BINARY(opcode)};
    for(int i = 0; i < 16; i++) {
        binary_str[i] = bits[i];
    }
    binary_str[16] = '\0'; // Null-terminate the string
}

/* Function: assemble
 * -------------------
 * Translate parsed instructions into binary and write to a .hack file
 *
 * file_name: the original .asm filename
 * instructions: array of parsed instructions
 * num_instructions: number of instructions parsed
 */
void assemble(const char *file_name, instruction* instructions, int num_instructions) {
    // Create the output filename by appending ".hack" to the input filename
    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.hack", file_name);

    // Open the output file for writing
    FILE *outfile = fopen(output_filename, "w");
    if (!outfile) {
        exit_program(EXIT_CANNOT_OPEN_FILE, output_filename);
    }

    // Variable address starts at 16 for variables
    hack_addr next_variable_address = 16;

    // Iterate over each instruction and translate to binary
    for (int i = 0; i < num_instructions; i++) {
        instruction current = instructions[i];
        char binary_code[17]; // 16 bits + null terminator

        if (current.type == A_TYPE_INSTR) {
            // Handle A-type instruction
            if (!current.instr.A_TYPE_INSTR.is_addr) {
                // It's a label; lookup in the symbol table
                Symbol *sym = symtable_find(current.instr.A_TYPE_INSTR.operand.label);
                if (sym != NULL) {
                    // Symbol found; use its address
                    hack_addr address = sym->address;
                    // Convert address to 16-bit binary
                    for(int bit = 15; bit >= 0; bit--) {
                        binary_code[15 - bit] = (address & (1 << bit)) ? '1' : '0';
                    }
                    binary_code[16] = '\0';
                } else {
                    // New variable; assign next available address
                    symtable_insert(current.instr.A_TYPE_INSTR.operand.label, next_variable_address);
                    hack_addr address = next_variable_address;
                    // Convert address to 16-bit binary
                    for(int bit = 15; bit >= 0; bit--) {
                        binary_code[15 - bit] = (address & (1 << bit)) ? '1' : '0';
                    }
                    binary_code[16] = '\0';
                    next_variable_address++;
                }
            } else {
                // It's a numeric address
                hack_addr address = current.instr.A_TYPE_INSTR.operand.address;
                // Convert address to 16-bit binary
                for(int bit = 15; bit >= 0; bit--) {
                    binary_code[15 - bit] = (address & (1 << bit)) ? '1' : '0';
                }
                binary_code[16] = '\0';
            }

            // Write the binary code to the output file
            fprintf(outfile, "%s\n", binary_code);
        }
        else if (current.type == C_TYPE_INSTR) {
            // Handle C-type instruction
            opcode op = instruction_to_opcode(current.instr.C_TYPE_INSTR);
            char temp_binary[17];
            opcode_to_binary_string(op, temp_binary);
            fprintf(outfile, "%s\n", temp_binary);
        }
        else {
            // Invalid instruction type
            fclose(outfile);
            exit_program(EXIT_ASSEMBLY_FAILED);
        }
    }

    // Close the output file
    fclose(outfile);
}
