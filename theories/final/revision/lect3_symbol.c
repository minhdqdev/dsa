#include <stdio.h>
#include <stdlib.h>
#include "libfdr/jrb.h"

#define INITIAL_SIZE 1
#define INCREMENTAL_SIZE 10

typedef struct{
    void *key;
    void *value;
} Entry;

typedef struct{
    Entry *entries;
    int size, total;
    Entry(*makeNode)(void*, void*);
    int(*compare)(void*, void*);
} SymbolTable;

SymbolTable createSymbolTable(){
}

int main(){


    return 0;
}