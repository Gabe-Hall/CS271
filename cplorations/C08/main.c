/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Gabriel Hall
 * [TERM] FALL 2024
 *
 * [DESCRIPTION] pseudo code was as follows:
 make sure there is an argument being passed, otherwise
 print a usage error message.
 next we need to open our file with an exit if there
 is an error opening said file.
 next we need to partse the file once its opened.
 lastly we need to close our file after we have parsed it.


 *
 ****************************************/
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "symtable.h"
#include "error.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }

    parse(file);

    fclose(file);
    return EXIT_SUCCESS;
}
