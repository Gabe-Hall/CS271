#include "symtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Symbol *hashArray[SYMBOL_TABLE_SIZE];

// djb2 hash function
int hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return (int)(hash % SYMBOL_TABLE_SIZE);
}

void symtable_insert(char *key, hack_addr addr) {
    struct Symbol *item = (struct Symbol *)malloc(sizeof(struct Symbol));
    item->name = strdup(key);
    item->addr = addr;

    int index = hash(key);
    while (hashArray[index] != NULL) {
        index = (index + 1) % SYMBOL_TABLE_SIZE;
    }
    hashArray[index] = item;
}

struct Symbol *symtable_find(char *key) {
    int index = hash(key);
    while (hashArray[index] != NULL) {
        if (strcmp(hashArray[index]->name, key) == 0)
            return hashArray[index];
        index = (index + 1) % SYMBOL_TABLE_SIZE;
    }
    return NULL;
}

void symtable_display_table() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("{%s, %d}\n", hashArray[i]->name, hashArray[i]->addr);
        }
    }
}

void symtable_print_labels() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("{%s,%d}\n", hashArray[i]->name, hashArray[i]->addr);
        }
    }
}
