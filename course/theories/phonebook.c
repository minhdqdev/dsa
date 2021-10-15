#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct phoneEntry{
    char name[80];
    long number;
} PhoneEntry;

typedef struct phoneBook{
    PhoneEntry *entries;
    int total;
    int size;
} PhoneBook;

PhoneBook createPhoneBook(){
    PhoneBook newPhoneBook;
    newPhoneBook.entries = (PhoneEntry*)malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
    newPhoneBook.total = 0;
    newPhoneBook.size = INITIAL_SIZE;

    return newPhoneBook;
}

void dropPhoneBook(PhoneBook *book){
    for(int i=0; i<book->total; i++){
        free(book->entries + i * sizeof(PhoneEntry));
    }
    free(book);
}

void addPhoneNumber(char *name, long number, PhoneBook *book){
    int foundIndex = -1;

    for(int i=0; i<book->total; i++){
        if(strcmp((book->entries+i*sizeof(PhoneEntry))->name, name) == 0){
            foundIndex = i;
            (book->entries+i*sizeof(PhoneEntry))->number = number;
            break;
        }
    }

    if(foundIndex == -1){
        if(book->total < book->size){
            strcpy((book->entries + total)->name, name);
            (book->entries + total)->number = number;
        }
        else{ // dynamic allocate
            book->size += INCREMENTAL_SIZE;
            PhoneEntry *newEntries = (PhoneEntry*)malloc(sizeof(PhoneEntry) * book->size);
            memcpy(newEntries, entries, sizeof(PhoneBook) * (book->size - INCREMENTAL_SIZE));
            free(book->entries);
            book->entries = newEntries;
        }
        total++;
    }
}

PhoneEntry *getPhoneNumber(char *name, PhoneBook book){

    return NULL;
}

int main(){

    return 0;
}