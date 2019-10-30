/*
Mini Project 1:
1. Add/Search/Delete with BTree
2. Autocomplete
3. Suggestion Search

Author: Dang Quang Minh (minh.dq176823@sis.hust.edu.vn)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.c"
#include "tab_completion.c"
#include "soundex.c"
#include "bt-5.0.0/inc/btree.h"
#include <time.h>
#include <sys/time.h>

#define START gettimeofday(&start, NULL);
#define END gettimeofday(&end, NULL);\
		    seconds = (end.tv_sec - start.tv_sec);\
		    micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);\
		    printf("\n>>Function's runtime: %ld seconds (%ld microseconds).\n", seconds, micros);

void getSuggestion(BTA* dictionary, char *word, char *suggestion[], int *n, int maxSuggestion){
    char soundexWord[50];
    strcpy(soundexWord, soundex(word));

    char meaning[50];
    char searchWord[50];

    strcpy(searchWord, word);

    int size;

    int i = 0;

    char *soundexTempWord = (char*)malloc(sizeof(char) * 50);

    btsel(dictionary, "", meaning, sizeof(meaning), &size);

    while(btseln(dictionary, searchWord, meaning, sizeof(meaning), &size) == 0){
        strcpy(soundexTempWord, soundex(searchWord));

        if(strcmp(soundexTempWord, soundexWord) == 0){
            strcpy(suggestion[i++], searchWord); // note; suggestion must have been malloc-ed.
        }

        if(i == maxSuggestion) break;
    }

    *n = i;
}

void printDictionary(BTA* dictionary, int length){
    int size;
    char meaning[100];
    char word[50];

    btsel(dictionary, "", (char*)&"", sizeof(char) * 100, &size);
    
    int i = 0;
    while(btseln(dictionary, word, meaning, sizeof(char) * 100, &size) == 0){
        printf("%s - %s\n", word, meaning);
        i++;
//        if(i > length){
//        	printf("Maximum number of words in dictionary reached!\n");
//        	break;
//		}
        if(i == length) break;
    }
}

void printDictionary2(BTA* dictionary, int length){
    int size;
    char meaning[100];
    char word[50];

    char tmpWord1[50];
    char tmpWord2[50];

    strcpy(tmpWord1, word);

    btsel(dictionary, "", (char*)&"", sizeof(char) * 100, &size);

    for(int i=0; i<100; i++){
        btseln(dictionary, word, meaning, sizeof(char) * 100, &size);
    }

    for(int i=0; i<length; i++){
        if(btselp(dictionary, word, meaning, sizeof(char) * 100, &size) == 0){
            strcpy(tmpWord2, word);

            printf("Compare; %s - %s - %d\n", tmpWord1, tmpWord2, strcmp(tmpWord1, tmpWord2));

            printf("%s - %s\n", word, meaning);

            strcpy(tmpWord1, tmpWord2);
        }
        else{
            perror("Error occured while reading dictionary.\n");
            continue;
        }
    }
}

void printMenu(){
	
	printf("\n---DICTIONARY---");
    printf("\n1. Add\n");
    printf("2. Search\n");
    printf("3. Delete\n");
    printf("4. Print\n");
    printf("5. Exit\n");
    printf("\nYour choice: ");
    
    
    
}

int main(){
	struct timeval sysStart, sysEnd;
	long sysSeconds, sysMicros;
	long long num;
	
	struct timeval start, end;
	long seconds, micros;
	
    char meaning[100];
    char word[50];
    char stripWord[50];
    int size;
	
	gettimeofday(&sysStart, NULL);
    printf("Authors:\n\tDang Quang Minh (minh.dq176823@sis.hust.edu.vn)\n\tNguyen Tri Hung (hung.nt176773@sis.hust.edu.vn)");
	
    BTA *dictionary;

    // Declaration for Advanced Search
    int ch, n;
    int prev_ch = '\0';
    char addition[50];
    // char stackString[50];
    char searchWord[50];
    CharStack *stack = createCharStack(50);

    char* dict[1000000];

    int maxSuggestion = 10;
    int numberSuggestion = 0;
    char* suggestion[maxSuggestion];
    for(int i=0; i<maxSuggestion; i++){
        suggestion[i] = (char*)malloc(sizeof(char) * 50);
    }


    int dictTotal = 0;

    int X = 8;
    int Y = 0;
    int Z = 1;
    
	init(); // init soundex

    btinit(); // init btree

    dictionary = btopn("dictionary.db", 0, 0);
	
    if(!dictionary){
        printf("Create my dictionary\n");
        dictionary = btcrt("dictionary.db", 0, 0);

        // FILE *fp = fopen("benchmark_large.txt", "r");
        FILE *fp = fopen("benchmark_1m.txt", "r");

        if(fp == NULL){
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
        }
        char buffer[50];
    	long long total = 0;
        while(fgets(buffer, 50, fp)){
            removeNewline(buffer);
            strcpy(word, buffer);

            meaning[0] = '\0';
            strcat(meaning, "Meaning of ");
            strcat(meaning, word);
            strcat(meaning, ".");

            // printf("%s - %s\n", word, meaning);

            if(btins(dictionary, word, meaning, sizeof(meaning))){
                printf("Error, can't insert %s\n", word);
                continue;
            }
			
            if(total % 100000 == 0){
            	printf("%lld words\nLoading...\n", total);	
			}

            total++;
        }

        printf("Total words in dictionary: %lld\n", total);
        fclose(fp);
    }

    int ans;
    int running = 1;
    while(running){
        printMenu();
        scanf("%d", &ans);
        while(getchar()!='\n');
		
		int isin;
		
        switch (ans){
        	
        // Check whether if word has newline
        case 1: // add
        	
            printf("Word: ");
            fgets(word, 50, stdin);
            removeNewline(word);

            printf("Meaning: ");
            fgets(meaning, 100, stdin);
            removeNewline(meaning);
			
			START
			
            isin = btins(dictionary, word, meaning, sizeof(meaning));
            if(isin == 46){
			    printf("Word has already existed! Update?[Y/n] ");
				fflush(stdin);
            	switch(getchar()){
        			case 'Y':
					case 'y':
						printf("Updated!\n");
        				btupd(dictionary, word, meaning, sizeof(meaning));
        				break;
        			case 'N':
        			case 'n':
        				printf("Did not update!\n");
        				break;
        			default:
        				printf("Wrong command! Did not update!\n");
        				break;
				}
			}
            
            END
            
			break;
        // case 5: // search // Interesting part
        //     printf("Word: ");
        //     fgets(word, 50, stdin);
        //     removeNewline(word);

        //     if(btsel(dictionary, word, meaning, sizeof(meaning), &size)){
        //         printf("Not found meaning of %s\n", word);
        //         break;
        //     }
        //     printf("Meaning of %s is: %s\n", word, meaning);
        //     break;
        case 3: // delete
        	
            printf("Word: ");
            fgets(word, 50, stdin);
            removeNewline(word);
			
			START
			
            btdel(dictionary, word);

            printf("Deleted %s\n", word);
            
        	END
            
            break;
        case 5: // exit
            running = 0;
            printf("Exiting...\n");
            break;
        case 2:
			
            X = 8;
            Y = 0;
            Z = 1;
            dictTotal = 0;

            while(!isEmpty(stack)) pop(stack);

            initscr();
            noecho();
            clear();
            
            addstr("Search: ");
            refresh();
            int running = 1;
            int flag = 0; // avoid to append the same word to dict
			
			
            while(running){
            	
            	
            	
                switch (ch = getch()){
                    case '\t': // press TAB
                        // TODO: create dict
                        
						START
                        
                        stackToString(stack, word);
                        strip(word, stripWord);
                        strcpy(searchWord, stripWord);

                        // update prev_ch
                        if(prev_ch == '\0') prev_ch = '\t';
                        else if(prev_ch == '\t'){
                            // double tab
                            // run suggestion search
                            if(btsel(dictionary, searchWord, meaning, sizeof(meaning), &size)){
                                getSuggestion(dictionary, stripWord, suggestion, &numberSuggestion, maxSuggestion);

                                move(1, 0);
                                deleteln();

                                if(numberSuggestion > 0){
                                    printw(">>> ");
                                    for(int i=0; i<numberSuggestion; i++){
                                        printw("%s  ", suggestion[i]);
                                    }
                                    printw("\n");
                                }
                                else{
                                    printw("<No suggestion>\n");
                                }
                                
                                move(Y, X);
                            }
                            
                        }

                        int count = 0;
                        if(strlen(word) == 0){ // empty word -> show the only one word in dict
                            btsel(dictionary, "", meaning, sizeof(meaning), &size);
                            while(btseln(dictionary, searchWord, meaning, sizeof(meaning), &size) == 0){
                                count++;

                                if(count > 1){
                                    
                                    break;
                                }
                            }
                            if(count == 1){
                                pushString(stack, searchWord);
                                push(stack, ' ');
                                X += strlen(searchWord)+1;
                                addstr(searchWord);
                                
                                move(Y, X);
                                break;
                            }
                            else break;
                        }

                        strip(word, stripWord);
                        strcpy(searchWord, stripWord);


                        btsel(dictionary, searchWord, meaning, sizeof(meaning), &size);
                        if(btsel(dictionary, searchWord, meaning, sizeof(meaning), &size)){ // not found ! Ex; test1.txt
                            while(1){
                                if(btseln(dictionary, searchWord, meaning, sizeof(meaning), &size)) break;

                                if(strBeginsWith(searchWord, stripWord)){
                                    // append to dict
                                    dict[dictTotal] = (char*)malloc(sizeof(char) * 50);
                                    strcpy(dict[dictTotal++], searchWord);
                                }
                                else break;
                            }
                        }
                        else{ // found ! 
                            dict[dictTotal] = (char*)malloc(sizeof(char) * 50);
                            strcpy(dict[dictTotal++], searchWord);
                        }

                        getAdditionStr(stripWord, dict, dictTotal, addition, &n);

                        if(strlen(addition) > 0){
                            if(n == 1){
                                pushString(stack, addition);
                                push(stack, ' ');
                                X += strlen(addition)+1;
                                addstr(addition);
                                
                                move(Y, X);
                            }
                            else if(n > 1){
                                pushString(stack, addition);
                                X += strlen(addition);
                                addstr(addition);
                                move(Y, X);
                            }
                        }
                        else{ // tim dc roi hoac ko tim dc gi ca
                            if(n > 1 ){
                                break;
                            }
                            else if(n == 1){
                                if(stripWord[strlen(stripWord)-1] != ' '){
                                    push(stack, ' ');
                                    mvaddch(Y, X++, ' ');
                                    move(Y, X);
                                }
                            }
                            else if(n == 0) break;
                            else{
                                // if(word[strlen(word)-1] != ' '){
                                if(stripWord[strlen(stripWord)-1] != ' '){
                                    push(stack, ' ');
                                    mvaddch(Y, X++, ' ');
                                    move(Y, X);
                                }
                            }
                        }
                        break;
                    case KEY_BACKSPACE: // press BACKSPACE
                    case 127:
                    case KEY_DC:
                    	
                    	START
                    	
                    case '\b':
                        // move(1, 0);
                        // deleteln();
                        // move(Y, X);
						
						START
						
                        if(prev_ch == '\t') prev_ch = '\0';

                        dictTotal = 0;

                        if(X > 8){
                            pop(stack);
                            mvdelch(Y, --X);
                        }
                        else{
                            while(!isEmpty(stack)) pop(stack);

                            move(1, 0);
                            deleteln();
                            move(0, 0);
                            deleteln();
                            X = 8;
                            Y = 0;
                            move(0, 0);
                            addstr("Search: ");
                            move(Y, X);
                        }
                        break;

                    case '\n': // press ENTER
                    case KEY_ENTER:
                    	
                    	START
                    	
                        prev_ch = '\0';

                        dictTotal = 0;
                        stackToString(stack, word);
                        running = 0;
                        break;
                    
                    default:
                    	
                    	START
                    	
                        prev_ch = '\0';

                        push(stack, ch);

                        mvaddch(Y, X++, ch);
                        break;
                }
                refresh();
            }
            endwin();

            // printf("YES %d\n", dictTotal);

            for(int i=0; i<dictTotal; i++){
                printf("Dict: %s\n", dict[i]);
            }

            strip(word, stripWord);

            if(btsel(dictionary, stripWord, meaning, sizeof(meaning), &size)){
                printf("Not found.\n");
            }
            else{
                printf("Meaning of %s is: %s\n", stripWord, meaning);
            }
			
			END
			
            break;
        case 4://Print
        	
        	printf("How many words do you want to print?(>= 1 word, if reached maximum number of words, printing will automatically stop) ");
        	scanf("%lld", &num);
        	
        	while(num <= 0){
        		printf("Wrong number! Input again: ");
        		scanf("%lld", &num);	
			}
        	
        	
        	
			START
        	
            printDictionary(dictionary, num);
            
            END
            
			break;
        default:
            printf("Wrong command!\n");
            break;
        }
    }

    // printDictionary(dictionary, 5);

    btcls(dictionary);
	
	gettimeofday(&sysEnd, NULL);
	sysSeconds = (sysEnd.tv_sec - sysStart.tv_sec);
    sysMicros = ((sysSeconds * 1000000) + sysEnd.tv_usec) - (sysStart.tv_usec);

    printf("\n>>Program's runtime: %ld seconds(%ld microseconds).\n", sysSeconds, sysMicros);
		
    return 0;
}
