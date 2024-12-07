<<<<<<< HEAD
#include "symtable.h"
#include <string.h>

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % SYMBOL_TABLE_SIZE;
}

void symtable_insert(char *key, hack_addr addr) {
    Symbol *item = malloc(sizeof(Symbol));
    item->address = addr;
    item->name = strdup(key);
    int hashIndex = hash(key);
    while (hashArray[hashIndex] != NULL) {
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }
    hashArray[hashIndex] = item;
}

Symbol *symtable_find(char *name) {
    int hashIndex = hash(name);
    while (hashArray[hashIndex] != NULL) {
        if (strcmp(hashArray[hashIndex]->name, name) == 0) {
            return hashArray[hashIndex];
        }
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }
    return NULL;
}
=======
#include "symtable.h"
#include <string.h>

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % SYMBOL_TABLE_SIZE;
}

void symtable_insert(char *key, hack_addr addr) {
    Symbol *item = malloc(sizeof(Symbol));
    item->address = addr;
    item->name = strdup(key);
    int hashIndex = hash(key);
    while (hashArray[hashIndex] != NULL) {
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }
    hashArray[hashIndex] = item;
}

Symbol *symtable_find(char *name) {
    int hashIndex = hash(name);
    while (hashArray[hashIndex] != NULL) {
        if (strcmp(hashArray[hashIndex]->name, name) == 0) {
            return hashArray[hashIndex];
        }
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }
    return NULL;
}
>>>>>>> 5543e7c8b71009152f6be1640862c34671550079
