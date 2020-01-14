#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"

#define INITIAL_SIZE 1
#define INCREMENTAL_SIZE 5

typedef struct{
    char name[80];
    long number;
} PhoneEntry;

typedef struct{
    PhoneEntry *entries;
    int total;
    int size;
} PhoneBook;

PhoneBook createPhoneBook(){
    PhoneBook newPB;
    newPB.size = INITIAL_SIZE;
    newPB.entries = (PhoneEntry*)malloc(sizeof(PhoneEntry) * newPB.size);
    newPB.total = 0;

    return newPB;
}

void dropPhoneBook(PhoneBook *book){
    free(book->entries);
    free(book);
}

void addPhoneNumber(char *name, long number, PhoneBook *book){
    int duplicated = 0;
    for(int i=0; i<book->total; i++){
        if(strcmp(book->entries[i].name, name) == 0){
            book->entries[i].number = number;
            duplicated = 1;
            break;
        }
    }
    if(!duplicated){
        if(book->total == book->size){
            PhoneEntry *tempEntries = (PhoneEntry*)malloc(sizeof(PhoneEntry) * (book->size + INCREMENTAL_SIZE));
            // memcpy(tempEntries, book->entries, sizeof(book->entries));
            for(int i=0; i<book->size; i++){
                memcpy(tempEntries+i, book->entries+i * sizeof(PhoneEntry), sizeof(PhoneEntry));
            }
            book->size += INCREMENTAL_SIZE;
            free(book->entries);
            book->entries = tempEntries;
        }

        strcpy(book->entries[book->total].name, name);
        book->entries[book->total++].number = number; 
    }
}

PhoneEntry *getPhoneNumber(char *name, PhoneBook book){
    for(int i=0; i<book.total; i++){
        if(strcmp(book.entries[i].name, name) == 0){
            return book.entries + i * sizeof(PhoneEntry);
        }
    }
    return NULL;
}

void printPhoneBook(PhoneBook book){
    printf("PhoneBook:\n");
    for(int i=0; i<book.total; i++){
        printf("%s - %ld\n", book.entries[i].name, book.entries[i].number);
    }
    printf("\n");
}

int main(){
    PhoneBook book = createPhoneBook();

    addPhoneNumber("Dang Quang Minh", 973389694, &book);

    printPhoneBook(book);

    addPhoneNumber("Dang Hai Loc", 963520636, &book);

    printPhoneBook(book);

    addPhoneNumber("Dang Quang Minh", 123456789, &book);

    printPhoneBook(book);



    return 0;
}