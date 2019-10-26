#include <ncurses.h>
#include "charstack.c"
int strBeginsWith(char* a, char* b){
    return !strncmp(a, b, strlen(b));
}

int getCommonIndex(char* a, char* b){
    int i = 0;
    
    int boundIndex = (strlen(a) <= strlen(b)) ? strlen(a)-1 : strlen(b)-1;

    // printf("BoundIndex: %d\n", boundIndex);

    while(a[i] == b[i] && i <= boundIndex) i++;

    return i-1;
}

int getAdditionStr(char *prefix, char* dictionary[], int length, char *result, int *n){
    char addition[50] = "";
    int commonIndex;
    char subString[50] = "";
    char tempPrefix[50] = "";

    int flag = 0;

    int count = 0;

    for(int i=0; i<length; i++){
        if(strBeginsWith(dictionary[i], prefix)){ // get all word in dictionary that starts with prefix
            count++;
            // printf("Found: %s \n", dictionary[i]);

            strncpy(subString, dictionary[i]+strlen(prefix), sizeof(dictionary[commonIndex+1]));

            

            commonIndex = getCommonIndex(addition, subString);

            // printf("SubString: %s - Addition: %s - Common: %d\n", subString, addition, commonIndex);

            if(commonIndex >= 0){
                addition[commonIndex+1] = '\0';
                
                // printf("Addition: %s\n", addition);
            }
            else{
                if(strlen(addition) == 0){
                    if(flag == 0){
                        flag = 1;
                        strcpy(addition, subString);
                    }
                    else{
                        break;
                    }
                }
                else{
                    strcpy(addition, "");
                }
            }
        }
    }

    strcpy(result, addition);
    *n = count;
}

int main(){
    char *dictionary[] = {"a.txt", "b.txt", "c.txt", "test1.txt", "test2.txt", "tet.txt", "w.txt"};
    int ch;
    char addition[50];
    CharStack *stack = createCharStack(50);
    char stackString[50];
    int n;

    char word[7][50] = {"a", "w.tx", "t", "te", "tes", "test1", "test2.txt"};

    for(int i=0; i<7; i++){
        getAdditionStr(word[i], dictionary, 7, addition, &n);
        printf("Word: '%s' - Addition: '%s' - Number: %d\n", word[i], addition, n);
    }
    
    for(int i=0; i<7; i++){
        pushString(stack, word[i]);
        stackToString(stack, stackString);

        printf("Word: %s - SStack: %s - Top: %d - ", word[i], stackString, stack->top);
        printStack(stack);

        while(!isEmpty(stack)) pop(stack);
    }

    return 0;
}