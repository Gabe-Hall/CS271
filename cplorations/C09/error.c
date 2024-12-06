#include "error.h"

const char *error_messages[] = {
    [EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]",
    [EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s",
    [EXIT_TOO_MANY_INSTRUCTIONS] = "File contains more than the maximum of %u instructions",
    [EXIT_INVALID_LABEL] = "Line %u: %s : Invalid label name",
    [EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s : Symbol is already defined",
    [EXIT_INVALID_A_INSTR] = "Line %u: %s : Invalid A-instruction operand"
};

void exit_program(enum exitcode code, ...) {
    va_list args;
    va_start(args, code);

    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, error_messages[code], args);
    fprintf(stderr, "\n");

    va_end(args);
    exit(code);
}
