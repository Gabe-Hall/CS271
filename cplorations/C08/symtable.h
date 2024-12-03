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
Symbol *symtable_find(char *key);
void symtable_insert(char *key, hack_addr addr);

#endif // __SYMTABLE_H__

