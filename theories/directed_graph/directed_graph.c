/*
Directed Graph implemented by Red-Black Tree

Author: minhdq99hp
*/
#include <stdio.h>

#include "libfdr/jrb.h"

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

char *getVertex(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);

    return jval_s(node->val);
}

void addEdge(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);
    
    if(node == NULL){
        JRB tree = make_jrb();
        node = jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }

    JRB subTree = (JRB)jval_v(node->val);
    jrb_insert_int(subTree, v2, new_jval_i(1));
}

int hasEdge(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);

    if(node == NULL) return 0;
    else{
        JRB subTree = (JRB)jval_v(node->val);
        JRB node2 = jrb_find_int(subTree, v2);

        if(node2 == NULL) return 0;
        else return 1;
    }
}

int indegree(Graph graph, int v, int *output){
    JRB node;

    int total = 0;

    jrb_traverse(node, graph.edges){
        JRB subTree = (JRB)jval_v(node->val);

        JRB foundNode = (JRB)jrb_find_int(subTree, v);

        if(foundNode != NULL) output[total++] = jval_i(node->key);
    }

    return total;
}

int outdegree(Graph graph, int v, int *output){
    JRB node = jrb_find_int(graph.edges, v);

    int total = 0;

    if(node == NULL) return total;

    JRB foundNode;
    JRB subTree = (JRB)jval_v(node->val);

    jrb_traverse(foundNode, subTree){
        output[total++] = jval_i(foundNode->key);
    }
    return total;
}

int DAG(Graph graph){
    // TODO:
}

void dropGraph(Graph graph){
    JRB node;

    jrb_free_tree(graph.vertices);
    jrb_traverse(node, graph.edges) jrb_free_tree(jval_v(node->val));
    jrb_free_tree(graph.edges);
}

void printVertices(Graph graph){
    JRB node;
    printf("Vertices:");
    jrb_traverse(node, graph.vertices){
        printf("%4s", jval_s(node->val));
    }
    printf("\n");
}

void printOutdegree(Graph graph, int v){
    int output[1000];
    int total;

    total = outdegree(graph, v, output);

    printf("Outdegree of %d:", v);
    JRB node;
    for(int i=0; i<total; i++){
        node = jrb_find_int(graph.vertices, output[i]);

        if(node != NULL) printf("%4s", jval_s(node->val));
    }
    printf("\n");
}

void printIndegree(Graph graph, int v){
    int output[1000];
    int total;

    total = indegree(graph, v, output);

    printf("Indegree of %d:", v);
    JRB node;
    for(int i=0; i<total; i++){
        node = jrb_find_int(graph.vertices, output[i]);

        if(node != NULL) printf("%4s", jval_s(node->val));
    }
    printf("\n");
}

int main(){
    Graph g = createGraph();

    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");

    printVertices(g);

    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 1, 3);

    printOutdegree(g, 1);
    printIndegree(g, 0);


    // if(DAG(g)) printf("The graph is a cycle\n");
    // else printf("Have cycles in the graph\n");

    return 0;
}