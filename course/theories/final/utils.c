#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int strBeginsWith(char* a, char* b){
    return !strncmp(a, b, strlen(b));
}

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

int hasNewline(char *str){
    int res = 0;
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == '\n'){
            res = 1;
            break;
        }
        i++;
    }
    return res;
}

void strip(char *str, char *result){
    // right strip
    int i=0;
    while(str[i] != '\0') i++;

    while(str[i-1] == ' ') i--;

    // left strip
    int j=0;
    while(str[j] == ' ') j++;

    strncpy(result, str+j, sizeof(char) * (i-j));
    result[i-j] = '\0';
}

int split(char *str, char *delim, char *output[]){
    int n = 0;
    char *token;

    token = strtok(str, delim);
    while(token != NULL){
        output[n++] = token;
        // printf("%s\n", token);
        token = strtok(NULL, delim);
    }

    return n;
}

// int main(){
//     char a[50] = "test1.txt";
//     char b[50] = "test1.txt ";

//     printf("%d\n", strBeginsWith(a, b));

//     char c[] = "1 2 10";

//     char *output[100];
//     int n = split(c, " ", output);

//     for(int i=0; i<n; i++) printf("%s\n", output[i]);
   
// }