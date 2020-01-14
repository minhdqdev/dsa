#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

JRB createGraph(){
    JRB graph = make_jrb();

    return graph;
}

void addEdge(JRB graph, int v1, int v2){
    JRB node = jrb_find_int(graph, v1);

    if(node == NULL){
        JRB subtree = make_jrb();
        jrb_insert_int(graph, v1, new_jval_v(subtree));
        node = subtree;
    }
    else node = (JRB)jval_v(node->val);
    
    JRB node2 = jrb_find_int(node, v2);
    if(node2 == NULL) jrb_insert_int(node, v2, new_jval_i(1));
}

int adjacent(JRB graph, int v1, int v2){
    JRB node = jrb_find_int(graph, v1);

    if(node == NULL) return 0;
    else{
        JRB subNode = jrb_find_int(node, v2);
        return subNode != NULL;
    }
}

int getAdjacentVertices(JRB graph, int v, int *output){
    int n=0;

    JRB node = jrb_find_int(graph, v);
    if(node != NULL){
        JRB subTree = (JRB)jval_v(node->val);

        jrb_traverse(node, subTree){
            output[n++] = jval_i(node->key);
        }
    }
    return n;
}

void dropGraph(JRB graph){
    JRB node;
    jrb_traverse(node, graph) jrb_free_tree(node);
    jrb_free_tree(graph);
}

void printVertex(int v){
    printf("%5d", v);
}

void BFS(JRB graph, int start, int stop, void(*func)(int)){
    int visited[1000];
    memset(visited, 0, sizeof(int) * 1000);
    JRB node;
    jrb_traverse(node, graph) visited[jval_i(node->key)] = 0;

    Dllist q = new_dllist();
    dll_append(q, new_jval_i(start));

    while(!dll_empty(q)){
        Dllist node = dll_first(q);
        int u = jval_i(node->val);
        dll_delete_node(node);

        if(!visited[u]){
            func(u);
            visited[u] = 1;

            if(u == stop) return;

            int output[1000];
            int n = getAdjacentVertices(graph, u, output);

            for(int i=0; i<n; i++){
                if(!visited[output[i]]) dll_append(q, new_jval_i(output[i]));
            }
        }
    }
}

void DFS(JRB graph, int start, int stop, void(*func)(int)){
    int visited[1000];
    memset(visited, 0, 1000);
    JRB node;
    jrb_traverse(node, graph) visited[jval_i(node->key)] = 0;

    Dllist s = new_dllist();
    dll_append(s, new_jval_i(start));

    while(!dll_empty(s)){
        Dllist node = dll_last(s);
        int u = jval_i(node->val);
        dll_delete_node(node);

        if(!visited[u]){
            func(u);
            visited[u] = 1;

            if(u == stop) return;

            int output[1000];
            int n = getAdjacentVertices(graph, u, output);

            for(int i=0; i<n; i++){
                if(!visited[output[i]]) dll_append(s, new_jval_i(output[i]));
            }
        }
    }
}

int main(){
    JRB g = createGraph();

    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 0, 1);

    int output[1000];
    int n = getAdjacentVertices(g, 0, output);

    printf("Adjacent vertices: ");
    for(int i=0; i<n; i++) printf("%5d", output[i]);
    printf("\n");

    BFS(g, 0, 1, printVertex);
    printf("\n");

    BFS(g, 0, -1, printVertex);
    printf("\n");

    DFS(g, 0, 2, printVertex);
    printf("\n");
    DFS(g, 0, -1, printVertex);
    printf("\n");

    return 0;
}