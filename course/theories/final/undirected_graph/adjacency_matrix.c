/*
Adjacency Matrix may be preferred when the graph is dense, 
or when we need to be able to tell quickly if there is an edge 
connecting two give vertices.

Author: minhdq99hp
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCREASE_SIZEMAX 5
#define INITIAL_SIZEMAX 5

typedef struct graph{
    int *matrix;
    int sizemax;
} Graph;

Graph createGraph(int sizemax){
    Graph* newGraph = (Graph*)malloc(sizeof(Graph));
    newGraph->matrix = (int*)malloc(sizeof(int) * sizemax * sizemax);
    memset(newGraph->matrix, 0, sizeof(int) * sizemax * sizemax);

    newGraph->sizemax = sizemax;
    return *newGraph;
}

void dropGraph(Graph *graph){
    graph->sizemax = 0;
    free(graph->matrix);
}

void addEdge(Graph *graph, int v1, int v2){
    if(v1 >= graph->sizemax || v2 >= graph->sizemax){
        int newSizemax = graph->sizemax + INCREASE_SIZEMAX;
        int *newMatrix = (int*)malloc(sizeof(int) * newSizemax * newSizemax);

        for(int row=0; row<graph->sizemax; row++){
            memcpy(newMatrix + row * newSizemax, graph->matrix + row * graph->sizemax, sizeof(int) * graph->sizemax);
        }
        free(graph->matrix);
        graph->matrix = newMatrix;
        graph->sizemax = newSizemax;

        printf("Expand matrix !\n");
    }


    graph->matrix[v1 * graph->sizemax + v2] = 1;
    graph->matrix[v2 * graph->sizemax + v1] = 1;
}   

int adjacent(Graph graph, int v1, int v2){
    return (graph.matrix[v1 * graph.sizemax + v2] == 1) ? 1 : 0;
}

int getAdjacentVertices(Graph graph, int vertex, int* output){
    int count = 0;
    for(int i=0; i<graph.sizemax; i++){
        if(graph.matrix[vertex * graph.sizemax + i] == 1){
            output[count++] = i;
        }
    }

    return count;
}

int main(){
    Graph graph = createGraph(INITIAL_SIZEMAX);

    printf("sizemax: %d\n", graph.sizemax);

    printf("g[2, 3]: %d\n", graph.matrix[2 * graph.sizemax + 3]);
    addEdge(&graph, 2, 3);
    printf("g[2, 3]: %d\n", graph.matrix[2 * graph.sizemax + 3]);
    printf("g[3, 2]: %d\n", graph.matrix[3 * graph.sizemax + 2]);
    
    addEdge(&graph, 1, 2);
    addEdge(&graph, 1, 3);

    printf("old sizemax: %d\n", graph.sizemax);
    addEdge(&graph, 1, 6);
    printf("new sizemax: %d\n", graph.sizemax);
    addEdge(&graph, 1, 10);
    printf("new sizemax: %d\n", graph.sizemax);

    int n;
    int output[graph.sizemax]; // set its size larger or you have to malloc it if you want to add new vertices.
    n = getAdjacentVertices(graph, 1, output);
    
    if(n == 0) printf("No adjacent vertices of node 1\n");
    else {
        printf("Adjacent vertices of node 1: ");
        for(int i=0; i<n; i++) printf("%5d", output[i]);
        printf("\n");
    }


    n = getAdjacentVertices(graph, 5, output);
    
    if(n == 0) printf("No adjacent vertices of node 5\n");
    else {
        printf("Adjacent vertices of node 5: ");
        for(int i=0; i<n; i++) printf("%5d", output[i]);
        printf("\n");
    }

    dropGraph(&graph);

    printf("sizemax: %d\n", graph.sizemax);

    return 0;
}