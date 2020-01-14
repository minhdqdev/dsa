#ifndef _WEIGHTED_GRAPH_H_
#define _WEIGHTED_GRAPH_H_

#include "libfdr/jrb.h"

typedef struct {
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();

void addVertex(Graph graph, int id, char *name);

char *getVertex(Graph graph, int id);

void addEdge(Graph graph, int v1, int v2, double weight);

double getEdgeValue(Graph graph, int v1, int v2);

int hasEdge(Graph graph, int v1, int v2);

int indegree(Graph graph, int v, int *output);

int outdegree(Graph graph, int v, int *output);

void dropGraph(Graph graph);

void printVertices(Graph graph);

void printOutdegree(Graph graph, int v);

void printIndegree(Graph graph, int v);

#endif