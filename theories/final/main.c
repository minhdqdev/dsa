/*
Final Exam IT3240E
Dang Quang Minh - 20176823
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

void readFile(const char *filename){
    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[500];
    while(fgets(buffer, 500, fp)){
        removeNewline(buffer);
        
    }

    fclose(fp);
}

void printMenu(){
    printf("1. Do something\n");
    printf("2. Do something\n");
    printf("3. Do something\n");
    printf("0. Exit program\n");
    printf("Your choice: ");
}

int main(int argc, char* argv[]){
    int ans;

    while(ans != 0){
        printMenu();
        scanf("%d", &ans);

        switch(ans){
            case 1: break;
            case 2: break;
            case 3: break;
            case 0: break;
        }
    }
    return 0;
}