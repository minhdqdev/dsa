/*
Mini Project 2:


Author: Dang Quang Minh (minh.dq176823@sis.hust.edu.vn)
*/

#include <stdio.h>
#include <stdlib.h>

#include "weighted_graph/weighted_graph.h"

#define EXIT_FAILURE -1

int loadGraph(const char *filename){    
    FILE *fp = fopen(filename, 'r');
    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    Graph g = createGraph();

    char buffer[1000];
    char routeId[10];
    char vertexName[200];
    char tempVertexName[200];
    int vertexId = 0;

    while(fgets(buffer, 1000, fp)){
        removeNewline(buffer);
        
        if(strlen(buffer) < 10){
            strcpy(routeId, buffer);
        }
        else{
            int p0 = 0; 
            int p1 = 0;

            while(buffer[p1] != '\0'){
                if(buffer[p1] == '-'){
                    strncpy(vertexName, buffer[p0], (p1-p0) * sizeof(char));

                    
                    

                    p0 = p1 + 1;
                }

                p1++;
            }
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
    Graph g = createGraph();

    return 0;
}