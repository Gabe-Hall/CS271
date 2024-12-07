#include "symtable.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % SYMBOL_TABLE_SIZE;
}

void symtable_insert(const char *key, hack_addr addr) {
    if (symtable_find(key)) return;  // Check for duplicate

    Symbol *item = malloc(sizeof(Symbol));
    if (!item) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    item->name = strdup(key);
    if (!item->name) {
        free(item);
        fprintf(stderr, "Failed to allocate name.\n");
        return;
    }

    item->address = addr;
    int hashIndex = hash(key);
    while (hashArray[hashIndex] != NULL) {
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }
    hashArray[hashIndex] = item;
}

Symbol *symtable_find(const char *name) {
    int hashIndex = hash(name);
    while (hashArray[hashIndex] != NULL) {
        if (strcmp(hashArray[hashIndex]->name, name) == 0) {
            return hashArray[hashIndex];
        }
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }
    return NULL;
}

void symtable_display_table() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("(%s, %d) ", hashArray[i]->name, hashArray[i]->address);
        } else {
            printf("~~ ");
        }
    }
    printf("\n");
}

void symtable_print_labels() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("{%s, %d}\n", hashArray[i]->name, hashArray[i]->address);
        }
    }
}
