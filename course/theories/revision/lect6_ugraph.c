#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCREMENTAL_SIZEMAX 5

typedef struct{
    int *matrix;
    int sizemax;
} Graph;

Graph createGraph(int sizemax){
    Graph newGraph;
    newGraph.matrix = (int*)malloc(sizeof(int) * sizemax * sizemax);
    memset(newGraph.matrix, 0, sizeof(int) * sizemax * sizemax);
    newGraph.sizemax = sizemax;
    return newGraph;
}

void addEdge(Graph *graph, int v1, int v2){
    if(v1 >= graph->sizemax || v2 >= graph->sizemax){
        int newSize = graph->sizemax + INCREMENTAL_SIZEMAX;
        while(v1 >= newSize || v2 >= newSize){
            newSize += INCREMENTAL_SIZEMAX;
        }

        int *newMatrix = (int*)malloc(sizeof(int) * newSize * newSize);
        memset(newMatrix, 0, sizeof(int) * newSize * newSize);

        for(int row=0; row<graph->sizemax; row++){
            memcpy(newMatrix + row * newSize, graph->matrix + row * graph->sizemax, sizeof(int) * graph->sizemax);
        }

        free(graph->matrix);
        graph->matrix = newMatrix;
        graph->sizemax = newSize;
    }

    *(graph->matrix + v1 * graph->sizemax + v2) = 1;
    *(graph->matrix + v2 * graph->sizemax + v1) = 1;
}

int adjacent(Graph graph, int v1, int v2){
    return graph.matrix[v1 * graph.sizemax + v2] == 1;
}

int getAdjacentVertices(Graph graph, int vertex, int *output){
    int n=0;

    for(int col=0; col<graph.sizemax; col++){
        if(graph.matrix[vertex * graph.sizemax + col] == 1) output[n++] = col;
    }

    return n;
}

void dropGraph(Graph graph){
    free(graph.matrix);
}

void printGraph(Graph graph){
    printf("Graph: \n");
    for(int row=0; row<graph.sizemax; row++){
        for(int col=0; col<graph.sizemax; col++){
            printf("%d ", graph.matrix[row * graph.sizemax + col]);
        }
        printf("\n");
    }
}

int main(){
    Graph g = createGraph(5);

    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 1, 10);

    int output[1000];
    int n = getAdjacentVertices(g, 1, output);
    if(n){
        printf("Adjacent vertices of node 1: ");
        for(int i=0; i<n; i++) printf("%5d", output[i]);
        printf("\n");
    }
    else printf("No adjacent vertices of node 1");


    printGraph(g);

    dropGraph(g);
    return 0;
}