/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 *
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#define MAX_LINE_LENGTH  200
bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
bool skip_blank_line(const char *line);

#endif


/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);
