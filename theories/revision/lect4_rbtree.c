#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"

JRB createPhoneBook(){
    return make_jrb();
}

void addPhoneEntry(char *name, long number, JRB book){
    JRB node = jrb_find_str(book, name);

    if(node == NULL){
        jrb_insert_str(book, name, new_jval_l(number));
    }
    else{
        node->val.l = number;
    }
}

void printPhoneBook(JRB book){
    JRB node;
    printf("PhoneBook:\n");
    jrb_traverse(node, book){
        printf("%s - %ld\n", jval_s(node->key), jval_l(node->val));
    }
    printf("\n");
}

long getPhoneNumber(char *name, JRB book){
    JRB node;
    jrb_traverse(node, book){
        if(strcmp(jval_s(node->key), name) == 0){
            return jval_l(node->val);
        }
    }
    return -1;
}

int main(){
    JRB book = createPhoneBook();

    addPhoneEntry("Dang Quang Minh", 973389694, book);
    addPhoneEntry("Dang Hai Loc", 963520636, book);

    printPhoneBook(book);

    addPhoneEntry("Dang Quang Minh", 123456789, book);

    printPhoneBook(book);

    addPhoneEntry("Nguyen Bich Diep", 94111688, book);

    printPhoneBook(book);

    printf("%ld\n", getPhoneNumber("Dang Hai oc", book));
    printf("%ld\n", getPhoneNumber("Dang Quang Minh", book));
} 