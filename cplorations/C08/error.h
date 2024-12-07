<<<<<<< HEAD
/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 *
 ****************************************/

#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

enum exitcode {
    EXIT_INCORRECT_ARGUMENTS,
    EXIT_CANNOT_OPEN_FILE,
    EXIT_TOO_MANY_INSTRUCTIONS,
    EXIT_INVALID_LABEL,
    EXIT_SYMBOL_ALREADY_EXISTS,
};

void exit_program(enum exitcode code, ...);

#endif // __ERROR_H__
=======
/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 *
 ****************************************/

#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

enum exitcode {
    EXIT_INCORRECT_ARGUMENTS,
    EXIT_CANNOT_OPEN_FILE,
    EXIT_TOO_MANY_INSTRUCTIONS,
    EXIT_INVALID_LABEL,
    EXIT_SYMBOL_ALREADY_EXISTS,
};

void exit_program(enum exitcode code, ...);

#endif // __ERROR_H__
>>>>>>> 5543e7c8b71009152f6be1640862c34671550079
