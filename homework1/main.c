/*
Homework 1: Undirected Graph

Author: Dang Quang Minh (minh.dq176823@sis.hust.edu.vn)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jrb.h"

#include "utils.c"

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

int adjacent(JRB g, char *station1, char *station2){
    JRB node = jrb_find_str(g, station1);

    if(node == NULL) return 0;
    else{
        JRB subtree = (JRB)jval_v(node->val);
        if(jrb_find_str(subtree, station2)) return 1;
        else return 0;
    }
}

void addEdge(JRB g, char *station1, char *station2){
    if(strcmp(station1, station2) == 0) return; // prevent adding a loop

    JRB node = jrb_find_str(g, station1);

    if(node == NULL){
        JRB tree = make_jrb();
        node = jrb_insert_str(g, station1, new_jval_v(tree));
    }

    JRB subtree = (JRB)jval_v(node->val);
    JRB valnode = jrb_find_str(subtree, station2);
    if(valnode == NULL) jrb_insert_str(subtree, station2, new_jval_i(1));
    

    node = jrb_find_str(g, station2);

    if(node == NULL){
        JRB tree = make_jrb();
        node = jrb_insert_str(g, station2, new_jval_v(tree));
    }

    subtree = (JRB)jval_v(node->val);
    valnode = jrb_find_str(subtree, station1);
    if(valnode == NULL) jrb_insert_str(subtree, station1, new_jval_i(1));
}

int getAdjacentVertices(JRB g, char *station, char *output[]){
    int count = 0;

    JRB node = (JRB)jrb_find_str(g, station);

    if(node != NULL){
        JRB subtree = (JRB)jval_v(node->val);

        jrb_traverse(node, subtree){
            output[count++] = jval_s(node->key);
        }
    }
    return count;
}

void dropGraph(JRB g){
    JRB node;

    jrb_traverse(node, g){
        JRB subtree = (JRB)jval_v(node->val);
        jrb_free_tree(subtree);
    }
    jrb_free_tree(g);
}

void loadGraphFromFile(JRB g, char* listStation[], int *countStation, const char *filename){
    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(-1);
    }

    char buffer[50];
    int flag = 0;
    while(fgets(buffer, 50, fp)){
        removeNewline(buffer);

        if(strcmp(buffer, "[STATIONS]") == 0){
            flag = 1;
            continue;
        }
        else if(strcmp(buffer, "[LINES]") == 0){
            flag = 2;
            continue;
        }

        if(flag == 1){
            int i = 0;
            while(buffer[i] != '=') i++;
            char id[10] = "\0";
            char name[50] = "\0";
            strncpy(id, buffer, i);
            strcpy(name, buffer+i+1);

            listStation[(*countStation)++] = (char*)newStation(id, name);            
        }
        else if(flag == 2){
            int i = 0;
            while(buffer[i] != '=') i++;
            char lines[50];
            strcpy(lines, buffer+i+1);

            int left = 0;
            int right = 0;
            char listAdjacentStationId[100][50];
            int countAdjacentStationId = 0;

            while(lines[right] != '\0'){
                if(lines[right++] == ' '){
                    strncpy(listAdjacentStationId[countAdjacentStationId++], lines+left, right-left-1);
                    left = right;
                    continue;
                }
            }
            strncpy(listAdjacentStationId[countAdjacentStationId++], lines+left, right-left);

            // for(int i=0; i<countAdjacentStationId-1; i++){
            //     for(int j=i+1; j<countAdjacentStationId; j++){
            //         char* station1;
            //         char* station2;
            //         for(int k=0; k<*countStation; k++){
            //             if(strcmp(((Station*)(listStation[k]))->id, listAdjacentStationId[i]) == 0) station1 = listStation[k];
            //             else if(strcmp(((Station*)(listStation[k]))->id, listAdjacentStationId[j]) == 0) station2 = listStation[k];
            //         }
            //         addEdge(g, (char*)station1, (char*)station2);
            //     }
            // }

            for(int i=0; i<countAdjacentStationId-1; i++){
                char *station1;
                char *station2;
                for(int k=0; k<*countStation; k++){
                    if(strcmp(((Station*)(listStation[k]))->id, listAdjacentStationId[i]) == 0) station1 = listStation[k];
                    else if(strcmp(((Station*)(listStation[k]))->id, listAdjacentStationId[i+1]) == 0) station2 = listStation[k];
                }
                addEdge(g, (char*)station1, (char*)station2);
            }
        }
    }
}

void print_menu(){
    printf("\n1. Find adjacent stations\n");
    printf("2. Print stations\n");
    printf("0. Exit\n");
    printf("Your choice ?: ");
}

char* getStationById(char *listStation[], int countStation, char* id){
    for(int i=0; i<countStation; i++){
        if(strcmp(((Station*)listStation[i])->id, id) == 0) return listStation[i];
    }
    return NULL;
}

char* getStationByName(char *listStation[], int countStation, char* name){
    for(int i=0; i<countStation; i++){
        if(strcmp(((Station*)listStation[i])->name, name) == 0) return listStation[i];
    }
    return NULL;
}

int main(){
    JRB graph = make_jrb();
    char *listStation[100];
    int countStation=0;

    loadGraphFromFile(graph, listStation, &countStation, "metro_lines_data.txt");
    printf("Loaded graph from file!\n");

    int running = 1;
    int ans;
    while(running){
        print_menu();
        scanf("%d", &ans); getchar();

        switch(ans){
            case 0: running = 0; dropGraph(graph); break;
            case 1:{
                char temp_ans[50];
                char ans[50];
                printf("\nEnter station's name (or id): ");
                fgets(temp_ans, 50, stdin); removeNewline(temp_ans); strip(temp_ans, ans);

                char *output[100];

                for(int i=0; i<100; i++) output[i] = (char*)malloc(sizeof(char*));

                char* station = getStationById(listStation, countStation, ans);
                if(station == NULL){
                    station = getStationByName(listStation, countStation, ans);
                    if(station == NULL){
                        perror("Can't find this station.\n");
                        break;
                    }
                }
                int n = getAdjacentVertices(graph, station, output);

                printf("Adjacent Stations: \n");
                for(int i=0; i<n; i++) printf("%s - %s\n", ((Station*)output[i])->id, ((Station*)output[i])->name);
                printf("\n");

                break;
            }
            case 2:{
                for(int i=0; i<countStation; i++) printf("Station: %s - %s\n", ((Station*)listStation[i])->id, ((Station*)listStation[i])->name);

                break;
            }
            default:{
                perror("Invalid command!");
                break;
            }
        }
    }
    return 0;
}