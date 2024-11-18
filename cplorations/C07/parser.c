/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include <stdbool.h>
#include <string.h>

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */

char *strip(char *s){
	char s_new[MAX_LINE_LENGTH + 1];
	int i = 0;

	for (char *s2 = s; *s2; s2++) {
		if(*s2 == '/' && *(s2+1) == '/') {
			break;
		}

		if(!isspace(*s2)) {
            s_new[i++] = *s2;
		}
	}
	s_new[i] = '\0';
	strcpy(s, s_new);

    return s;
}

char *extract_label(const char *line, char *label) {
    int length = strlen(line);

    // Check if the line has parentheses as expected
    if (line[0] == '(' && line[length - 1] == ')') {
        strncpy(label, line + 1, length - 2); // Copy without the parentheses
        label[length - 2] = '\0'; // Null-terminate the string
    }

    return label;
}


bool is_Atype(const char *line) {
    return line[0] == '@';

}

bool is_label(const char *line) {
    int len = strlen(line);
    return len > 1 && line[0] == '(' && line[len - 1] == ')';
}

bool is_Ctype(const char *line) {
    return line[0] != '@' && line[0] != '(' && !skip_blank_line(line);
}


bool skip_blank_line(const char *line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) {
            return false;
        }
        line++;
    }
    return true;
}



/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments.
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */

void parse(FILE *file) {
    char line[256];
    int rom_address = 0;

    while (fgets(line, sizeof(line), file)) {
        strip(line); // Remove comments and whitespace

        if (skip_blank_line(line)) {
            continue; // Skip blank lines
        }

        if (is_Atype(line)) {
            rom_address++;
        } else if (is_label(line)) {
            char label[MAX_LABEL_LENGTH];
            extract_label(line, label); // Extract the label without parentheses
            symtable_insert(label, rom_address);

        } else if (is_Ctype(line)) {
            rom_address++;
        }

    }
}
