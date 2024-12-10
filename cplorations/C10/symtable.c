#include "symtable.h"

struct Symbol* hashArray[SYMBOL_TABLE_SIZE] = {NULL};

/* Function: hash
 * --------------
 * Simple hash function (djb2)
 *
 * str: the string to hash
 *
 * returns: hash index
 */
int hash(const char *str) {
    unsigned long hash_val = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash_val = ((hash_val << 5) + hash_val) + c; // hash * 33 + c
    }
    hash_val %= SYMBOL_TABLE_SIZE;
    return (int)hash_val;
}

/* Function: symtable_insert
 * -------------------------
 * Insert a symbol into the symbol table
 *
 * key: symbol name
 * addr: address associated with the symbol
 */
void symtable_insert(const char* key, hack_addr addr) {
    Symbol *item = (Symbol *)malloc(sizeof(Symbol));
    item->address = addr;
    item->name = strdup(key);

    int hashIndex = hash(key);
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL) {
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }
    hashArray[hashIndex] = item;
}

/* Function: symtable_find
 * -----------------------
 * Find a symbol in the symbol table
 *
 * name: symbol name to find
 *
 * returns: pointer to Symbol if found, NULL otherwise
 */
Symbol *symtable_find(const char *name) {
    int hashIndex = hash(name);
    while (hashArray[hashIndex] != NULL) {
        if (strcmp(hashArray[hashIndex]->name, name) == 0)
            return hashArray[hashIndex];
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }
    return NULL;
}

/* Function: symtable_display_table
 * -------------------------------
 * Display the entire symbol table (for debugging)
 */
void symtable_display_table() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != NULL)
            printf(" (%s,%d)", hashArray[i]->name, hashArray[i]->address);
        else
            printf(" ~~ ");
    }
    printf("\n");
}

/* Function: symtable_print_labels
 * -------------------------------
 * Print all labels and their addresses
 */
void symtable_print_labels() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("{%s,%d}\n", hashArray[i]->name, hashArray[i]->address);
        }
    }
}
