#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeNewline(char *str){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == '\n'){
            str[i] = '\0';
            break;
        }
        i++;
    }
}

int main(){
    printf("%d\n", strcmp("tet", "test1"));
    return 0;
}