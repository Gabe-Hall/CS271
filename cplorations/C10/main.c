// main.c

#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    const char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        exit_program(EXIT_CANNOT_OPEN_FILE, file_name);
    }

    instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
    if (instructions == NULL) {
        fclose(file);
        exit_program(EXIT_OUT_OF_MEMORY);
    }

    int num_instructions = parse(file, instructions);
    fclose(file);

    // Call assemble function directly since it returns void
    assemble(file_name, instructions, num_instructions);

    free(instructions);

    return 0;
}
