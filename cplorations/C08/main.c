<<<<<<< HEAD
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
#include "parser.h"
#include "symtable.h"
#include "error.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    const char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        exit_program(EXIT_CANNOT_OPEN_FILE, file_name);
    }

    parse(file);

    fclose(file);
    return 0;
}
=======
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
#include "parser.h"
#include "symtable.h"
#include "error.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    const char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        exit_program(EXIT_CANNOT_OPEN_FILE, file_name);
    }

    parse(file);

    fclose(file);
    return 0;
}
>>>>>>> 5543e7c8b71009152f6be1640862c34671550079
