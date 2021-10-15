#include <ncurses.h>
#include <string.h>
#include "charstack.c"

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

            // printw("%s - %s\n", dictionary[i], prefix);

            strncpy(subString, dictionary[i]+strlen(prefix), sizeof(dictionary[commonIndex+1]));

            commonIndex = getCommonIndex(addition, subString);

            if(commonIndex >= 0){
                addition[commonIndex+1] = '\0';
            }
            else{
                if(strlen(addition) == 0){
                    if(flag == 0){
                        flag = 1;
                        strcpy(addition, subString);
                    }
                    else break;
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

// int main(){
//     char *dictionary[] = {"a.txt", "b.txt", "c.txt", "test1.txt", "test2.txt", "tet.txt", "w.txt", "Hello", "hello"};
//     int ch;
//     char addition[50];
//     CharStack *stack = createCharStack(50);
//     char stackString[50];
//     int n;

//     initscr();
//     noecho();
//     int X = 8;
//     int Y = 0;
//     addstr("Search: ");

//     refresh();

//     int running = 1;
//     while(running){
//         switch (ch = getch()){
//             case '\t': // press TAB
//                 stackToString(stack, stackString);

//                 getAdditionStr(stackString, dictionary, 9, addition, &n);

//                 if(strlen(addition) > 0){
//                     if(n == 1){
//                         pushString(stack, addition);
//                         push(stack, ' ');
//                         X += strlen(addition)+1;
//                         addstr(addition);
                        
//                         move(Y, X);
//                     }
//                     else if(n > 1){
//                         pushString(stack, addition);
//                         X += strlen(addition);
//                         addstr(addition);
//                         move(Y, X);
//                     }
                    
//                 }
//                 break;
//             case KEY_BACKSPACE: // press BACKSPACE
//             case 127:
//             case KEY_DC:
//             case '\b':
//                 if(X > 8){
//                     pop(stack);
//                     mvdelch(Y, --X);
//                 }
//                 else{
//                     while(!isEmpty(stack)) pop(stack);

//                     deleteln();
//                     X = 8;
//                     Y = 0;
//                     move(0, 0);
//                     addstr("Search: ");
//                     move(Y, X);
//                 }
//                 break;

//             case '\n': // press ENTER
//             case KEY_ENTER:
//                 running = 0;
//                 break;
            
//             default:
//                 push(stack, ch);

//                 mvaddch(Y, X++, ch);
//                 break;
//         }
//         refresh();
//     }
//     endwin();

//     printStack(stack);
//     return 0;
// }