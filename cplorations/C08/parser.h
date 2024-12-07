<<<<<<< HEAD
/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 *
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

char *strip(char *s);
void parse(FILE *file);
bool is_Atype(const char *line);
bool is_label(const char *line);
bool is_Ctype(const char *line);
char *extract_label(const char *line, char *label);

#endif // __PARSER_H__
=======
/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 *
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

char *strip(char *s);
void parse(FILE *file);
bool is_Atype(const char *line);
bool is_label(const char *line);
bool is_Ctype(const char *line);
char *extract_label(const char *line, char *label);

#endif // __PARSER_H__
>>>>>>> 5543e7c8b71009152f6be1640862c34671550079
