#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct {
    void *key;
    void *value;
} Entry;

typedef struct {
    Entry *entries;
    int size, total;

    Entry (*makeNode)(void*, void*);
    int (*compare)(void*, void*);
} SymbolTable;

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*), int(*compare)(void*, void*)){

}

void dropSymbolTable(SymbolTable* tab);

void addEntry(void *key, void* value, SymbolTable *book);

Entry* getEntry(void* key, SymbolTable book);