#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

enum exitcode {
    EXIT_INCORRECT_ARGUMENTS,
    EXIT_CANNOT_OPEN_FILE,
    EXIT_TOO_MANY_INSTRUCTIONS,
    EXIT_INVALID_LABEL,
    EXIT_SYMBOL_ALREADY_EXISTS,
    EXIT_INVALID_A_INSTR,
    EXIT_INVALID_C_DEST,
    EXIT_INVALID_C_COMP,
    EXIT_INVALID_C_JUMP,
    EXIT_OUT_OF_MEMORY,          // New error code
    EXIT_ASSEMBLY_FAILED         // New error code
};

void exit_program(enum exitcode code, ...);

#endif // __ERROR_H__
