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

int main(int argc, const char *argv[])
{

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		perror("Error opening the file.\n");
		return EXIT_FAILURE;
	}

	parse(file);

	fclose(file);
	return EXIT_SUCCESS;

}


