#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

typedef struct{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph(){
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
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
    if(node == NULL) return NULL;
    return jval_s(node->val);
}

void addEdge(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);
    if(node == NULL){
        JRB subTree = make_jrb();
        jrb_insert_int(graph.edges, v1, new_jval_v(subTree));
        jrb_insert_int(subTree, v2, new_jval_i(1));
    }
    else{
        JRB subTree = (JRB)jval_v(node->val);
        JRB subNode = jrb_find_int(subTree, v2);
        if(subNode == NULL) jrb_insert_int(subTree, v2, new_jval_i(1));
    }
}

int hasEdge(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);
    if(node == NULL) return 0;
    else{
        node = jrb_find_int(node, v2);
        return node != NULL;
    }
}

int indegree(Graph graph, int v, int *output){
    JRB node;
    int n = 0;
    jrb_traverse(node, graph.edges){
        JRB subTree = (JRB)jval_v(node->val);
        JRB subNode;
        jrb_traverse(subNode, subTree){
            if(jval_i(subNode->key) == v){
                output[n++] = jval_i(node->key);
                break;
            }
        }
    }

    return n;
}

int outdegree(Graph graph, int v, int *output){
    JRB node = jrb_find_int(graph.edges, v);
    int n=0;
    if(node != NULL){
        JRB subNode;
        JRB subTree = (JRB)jval_v(node->val);
        jrb_traverse(subNode, subTree){
            output[n++] = jval_i(subNode->key); 
        }
    }
    return n;    
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

int DAG(Graph graph){
    int start;
    // int stop = -1;
    JRB node;
    jrb_traverse(node, graph.vertices){ // Do DFS with every vertices
        start = jval_i(node->key);

        int visited[1000];
        memset(visited, 0, 1000);

        JRB subNode;
        jrb_traverse(subNode, graph.edges) visited[jval_i(subNode->key)] = 0; 

        Dllist s = new_dllist();
        dll_append(s, new_jval_i(start));

        while(!dll_empty(s)){
            Dllist node = dll_last(s);
            int u = jval_i(node->val);
            dll_delete_node(node);

            if(!visited[u]){
                visited[u] = 1;

                int output[1000];
                int n = outdegree(graph, u, output);

                for(int i=0; i<n; i++){
                    if(!visited[output[i]]) dll_append(s, new_jval_i(output[i]));
                    else{
                        if(output[i] == start) return 0;                    
                    }
                }
            }
        }
    } 
    return 1;
}

void dropGraph(Graph graph){
    jrb_free_tree(graph.vertices);
    JRB node;
    jrb_traverse(node, graph.edges) jrb_free_tree((JRB)jval_v(node->val));
    jrb_free_tree(graph.edges);
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

void printVertices(Graph graph){
    JRB node;
    printf("Vertices:");
    jrb_traverse(node, graph.vertices){
        printf("%4s", jval_s(node->val));
    }
    printf("\n");
}

void topologicialSort(Graph graph, int *output, int *n){
    Dllist q = new_dllist();
    JRB node;
    int tempOutput[1000];
    jrb_traverse(node, graph.vertices){
        if(indegree(graph, jval_i(node->key), tempOutput) == 0){
            dll_append(q, node->key);    
        }
    }

    while(!dll_empty(q)){
        Dllist item = dll_first(q);
        int v = jval_i(item->val);
        dll_delete_node(item);

        output[*n++] = v;

        int k = outdegree(graph, v, tempOutput);

        

        int tempOutput2[1000];
        for(int i=0; i<k; i++){
            printf("v: %d - i: %d - k: %d\n", v, i, k);
            if(indegree(graph, tempOutput[i], tempOutput2) - 1 == 0){   
                printf("v: %d - %d\n", v, tempOutput[i]);
                dll_append(q, new_jval_i(tempOutput[i]));
            }
        }
    }

    free_dllist(q);
}

int main(){
    Graph g = createGraph();

    addVertex(g, 0, "CS102");
    addVertex(g, 1, "CS140");
    addVertex(g, 2, "CS160");
    addVertex(g, 3, "CS302");
    addVertex(g, 4, "CS311");
    addVertex(g, 5, "MATH300");

    // printVertices(g);
    // printOutdegree(g, 2);
    // printIndegree(g, 2);

    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 5, 4);
    addEdge(g, 3, 4);

    if(!DAG(g)){
        printf("Can not make topological sort\n");
        return 1;
    }
    int output[1000];
    int n = 0;
    topologicialSort(g, output, &n);

    printf("The topological order: \n");
    for(int i=0; i<n; i++){
        printf("%s\n", getVertex(g, output[i]));
    }

    dropGraph(g);
    return 0;
}