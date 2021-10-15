#include <stdio.h>
#include <stdlib.h>

#include "libfdr/jrb.h"

#define INF 1000000

typedef struct {
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

void addEdge(Graph graph, int v1, int v2, double weight){
    JRB node = jrb_find_int(graph.edges, v1);
    
    if(node == NULL){
        JRB tree = make_jrb();
        node = jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }

    JRB subTree = (JRB)jval_v(node->val);
    jrb_insert_int(subTree, v2, new_jval_d(weight));
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
