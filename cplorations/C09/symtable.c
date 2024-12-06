#include "symtable.h"
#include <string.h>
#include <stdlib.h>

struct Symbol *hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % SYMBOL_TABLE_SIZE;
}

void symtable_insert(char *key, hack_addr addr) {
    if (symtable_find(key)) return;

    Symbol *item = malloc(sizeof(Symbol));
    if (!item) return;

    item->name = strdup(key);
    item->address = addr;

    int index = hash(key);
    while (hashArray[index]) {
        index = (index + 1) % SYMBOL_TABLE_SIZE;
    }
    hashArray[index] = item;
}

Symbol *symtable_find(char *name) {
    int index = hash(name);
    while (hashArray[index]) {
        if (strcmp(hashArray[index]->name, name) == 0) {
            return hashArray[index];
        }
        index = (index + 1) % SYMBOL_TABLE_SIZE;
    }
    return NULL;
}
