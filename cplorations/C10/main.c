#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        // Incorrect number of arguments
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    const char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }

    instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
    if (!instructions) {
        fclose(file);
        exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTION_COUNT);
    }

    parse(file, instructions); // Removed 'num_instructions' variable
    // printf("Total Instructions Parsed: %d\n", num_instructions); // Removed
    // symtable_print_labels(); // Removed

    fclose(file);
    free(instructions);
    return 0;
}
