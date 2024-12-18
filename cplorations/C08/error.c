<<<<<<< HEAD
/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Gabriel Hall
 * [TERM] FALL 2024
 *
 ****************************************/
#include "error.h"

const char *error_messages[] = {
    [EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]",
    [EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s",
    [EXIT_TOO_MANY_INSTRUCTIONS] = "File contains more than the maximum of %u instructions",
    [EXIT_INVALID_LABEL] = "Line %u: %s : Invalid label name",
    [EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s : Symbol is already defined",
};

void exit_program(enum exitcode code, ...) {
    va_list arguments;
    va_start(arguments, code);

    printf("ERROR: ");
    vfprintf(stdout, error_messages[code], arguments);
    printf("\n");

    va_end(arguments);
    exit(code);
}
=======
/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Gabriel Hall
 * [TERM] FALL 2024
 *
 ****************************************/
#include "error.h"

const char *error_messages[] = {
    [EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]",
    [EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s",
    [EXIT_TOO_MANY_INSTRUCTIONS] = "File contains more than the maximum of %u instructions",
    [EXIT_INVALID_LABEL] = "Line %u: %s : Invalid label name",
    [EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s : Symbol is already defined",
};

void exit_program(enum exitcode code, ...) {
    va_list arguments;
    va_start(arguments, code);

    printf("ERROR: ");
    vfprintf(stdout, error_messages[code], arguments);
    printf("\n");

    va_end(arguments);
    exit(code);
}
>>>>>>> 5543e7c8b71009152f6be1640862c34671550079
