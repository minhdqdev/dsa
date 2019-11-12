#include <stdio.h>
#include <stdlib.h>

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
    free(book->entries);
    free(book);
}

void addPhoneNumber(char *name, long number, PhoneBook *book){
    int foundIndex = -1;

    for(int i=0; i<book->total; i++){
        if(book->entries+i)
    }
}

int main(){

    return 0;
}