#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdlib.h>
#include <stdint.h>

#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

typedef struct Symbol {
    char *name;
    hack_addr address;
} Symbol;

int hash(char *str);
void symtable_insert(char *key, hack_addr addr);
Symbol *symtable_find(char *name);
void symtable_print_labels();

#endif
