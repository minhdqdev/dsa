#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct station{
    char id[10];
    char name[50];
} Station;


Station* newStation(char *id, char *name){
    Station* newStation = (Station*)malloc(sizeof(Station));
    strcpy(newStation->id, id);
    strcpy(newStation->name, name);

    return newStation;
}


int main(){
    Station* s = newStation("S1", "Lang");

    char *p[100];
    int c = 0;
    p[c++] = (char*)newStation("S2", "Do Son");

    for(int i=0; i<1; i++){
        printf("Station: %s - %s\n", ((Station*)p[i])->id, ((Station*)p[i])->name);

    }
    
    return 0;
}