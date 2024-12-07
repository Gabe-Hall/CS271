#include "parser.h"
#include "symtable.h"
#include "error.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        // incorrect number of arguments
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }
    const char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }
    parse(file);
    symtable_print_labels();
    fclose(file);
    return 0;
}
