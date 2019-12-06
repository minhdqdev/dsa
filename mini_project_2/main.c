#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jrb.h"
#include "utils.c"

#define INF 1000000

typedef struct{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph(){
    Graph newGraph;

    newGraph.edges = make_jrb();
    newGraph.vertices = make_jrb();

    return newGraph;
}

void addVertex(Graph graph, int id, char *name){
    JRB node = jrb_find_int(graph.vertices, id);

    if(node == NULL){
        jrb_insert_int(graph.vertices, id, new_jval_s(name));
    }
    else{
        node->val = new_jval_s(name);
    }
}

char *getVertexNameById(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);

    return jval_s(node->val);
}

int getVertexIdByName(Graph graph, char *name){
    JRB node;

    jrb_traverse(node, graph.vertices){
        if(strcmp(name, jval_s(node->val)) == 0) return jval_i(node->key);
    }

    return -1;
}

void addEdge(Graph graph, int v1, int v2, double weight){
    JRB node = jrb_find_int(graph.edges, v1);
    
    if(node == NULL){
        JRB tree = make_jrb();
        node = jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }

    JRB subTree = (JRB)jval_v(node->val);

    JRB subNode = jrb_find_int(subTree, v2);

    if(subNode == NULL){
        jrb_insert_int(subTree, v2, new_jval_d(weight));
    }
    
}

double getEdgeValue(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);

    if(node == NULL) return INF;
    else{
        JRB subTree = (JRB)jval_v(node->val);
        JRB node2 = jrb_find_int(subTree, v2);

        if(node2 == NULL) return INF;
        else return jval_d(node2->val);
    }
}

void print_menu(){
    printf("1. Find shortest path\n");
    printf("0. Exit\n");
    printf("Your choice: ");
}

void printVertices(Graph graph){
    JRB node;
    printf("Vertices:");
    jrb_traverse(node, graph.vertices){
        printf("%d : %s\n", jval_i(node->key), jval_s(node->val));
    }
    printf("\n");
}

void loadFromFile(Graph graph, const char *filename){
    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[200];
    char *route_id;
    int flag = -1;
    while(fgets(buffer, 200, fp)){
        removeNewline(buffer);

        if(strcmp(buffer, "# VERTICES") == 0){
            flag = 0;
            continue;
        }
        else if(strcmp(buffer, "# ROUTE_ID") == 0){
            flag = 1;
            continue;
        }
        else if(strcmp(buffer, "## EDGES") == 0){
            flag = 2;
            continue;
        }

        if(flag == 0){ // read vertices
            int index = 0; // index of ':' character
            int id;
            char *verticeName = (char*)malloc(sizeof(char) * 100);
            char verticeId[10];

            while(buffer[index] != '\0'){
                if(buffer[index] == ':'){
                    strncpy(verticeId, buffer, index-1);
                    id = atoi(verticeId);

                    strncpy(verticeName, buffer+index+2, sizeof(verticeName));
                    addVertex(graph, id, verticeName);
                    break;
                }
                index++;
            }   
        } 
        else if(flag == 1){ // read route_id
            route_id = (char*)malloc(sizeof(char) * 20);
            strncpy(route_id, buffer, sizeof(route_id));
        }
        else if(flag == 2){ // read edges
            int rindex = 0; // index of the first space character
            int lindex = 0; // index of the last space character

            // printf("%s\n", buffer);
            char *temp;
            while(buffer[rindex] != '\0'){
                if(buffer[rindex] == ' '){
                    if(lindex == 0) lindex = rindex;
                    else{
                        int v1, v2, weight;
                        // get vertex 1
                        temp = (char*)malloc(sizeof(char) * 20);
                        strncpy(temp, buffer, lindex);
                        v1 = atoi(temp);
                        // get vertex 2
                        temp = (char*)malloc(sizeof(char) * 20);
                        strncpy(temp, buffer+lindex+1, rindex-lindex-1);
                        v2 = atoi(temp);
                        // get weight of edge
                        weight = atof(buffer+rindex+1);

                        addEdge(graph, v1, v2, weight);
                        break;
                    }
                }
                rindex++;
            }
            // free(temp);
        }
    }

    // printVertices(graph);
    fclose(fp);
}

void dropGraph(Graph graph){
    JRB node;

    jrb_traverse(node, graph.vertices){
        free(jval_s(node->val));
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

int main(){
    // load graph from file
    Graph g = createGraph();

    loadFromFile(g, "output.txt");

    // int running = 1;

    // while(running){
    //     int ans;

    //     print_menu();
    //     scanf("%d", &ans);

    //     switch(ans){
    //         case 1:{
    //             // finding shortest path
    //             int v1;
    //             int v2;
    //             char name1[100] = "Tran Hung Dao";
    //             char name2[100] = "Hai Ba Trung";
    //             v1 = getVertexIdByName(g, name1);
    //             v2 = getVertexIdByName(g, name2);

    //             // n is the number of vertices
    //             // output is the array of vertices' id (or name)
    //             // Ex: 01 -> 04 -> 26
    //             int n = findShortestPath(g, v1, v2, output);

    //             // n is the number of route
    //             // input is the array of vertices' id
    //             // output is the array of route
    //             // Ex: 01 -> 5A -> 21A 
    //             int n = getRouteFromPath(g, input, output);
    //             break;
    //         }
    //         case 0:{
    //             running = 0;
    //             dropGraph(g);
    //             printf("Exit program !\n");
    //             break;
    //         }
    //     }
    // }
    return 0;
}