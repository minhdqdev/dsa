/*
Search graph using DFS and BFS
*/

#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

#include <stdio.h>

void addEdge(JRB g, int v1, int v2){
    JRB node = jrb_find_int(g, v1);

    if(node == NULL){
        JRB tree = make_jrb();
        node = jrb_insert_int(g, v1, new_jval_v(tree));
    }

    JRB subTree = (JRB)jval_v(node->val);
    jrb_insert_int(subTree, v2, new_jval_i(1));

    node = jrb_find_int(g, v2);

    if(node == NULL){
        JRB tree = make_jrb();
        node = jrb_insert_int(g, v2, new_jval_v(tree));
    }

    subTree = (JRB)jval_v(node->val);
    jrb_insert_int(subTree, v1, new_jval_i(1));
}

int adjacent(JRB g, int v1, int v2){
    JRB node = jrb_find_int(g, v1);

    if(node == NULL) return 0;
    else{
        JRB subtree = (JRB)jval_v(node->val);
        if(jrb_find_int(subtree, v2)) return 1;
        else return 0;
    }
}

int getAdjacentVertices(JRB g, int vertex, int *output){
    int count = 0;
    
    JRB node = (JRB)jrb_find_int(g, vertex);

    if(node == NULL) return 0;
    else{
        JRB subTree = (JRB)jval_v(node->val);

        jrb_traverse(node, subTree){
            output[count++] = jval_i(node->key);
        }
    }

    return count;
}

void dropGraph(JRB g){
    JRB node;

    jrb_traverse(node, g){
        jrb_free_tree(jval_v(node->val));
    }

    jrb_free_tree(g);
}

void printVertex(int v){
    printf("%4d", v);
}

void BFS(JRB graph, int start, int stop, void(*func)(int)){
    /*
    Input:
        start: the first vertex to visit
        stop: the vertex to be visited at the end, if stop = -1, all the vertices may be visited
        func: a pointer to the function that process on the visited vertices
    */
    int visited[100];

    JRB vertex = NULL;
    Dllist queue = new_dllist();


    jrb_traverse(vertex, graph) visited[jval_i(vertex->key)] = 0;
    

    dll_append(queue, new_jval_i(start));

    while(!dll_empty(queue)){
        // pop queue
        Dllist node = dll_first(queue);
        int v = jval_i(node->val);
        dll_delete_node(node);

        if(!visited[v]){
            func(v);
            visited[v] = 1;

            if(v == stop) return;
            int adjacentVertices[100];
            int n = getAdjacentVertices(graph, v, adjacentVertices);

            for(int i=0; i<n; i++){
                if(!visited[adjacentVertices[i]]){
                    dll_append(queue, new_jval_i(adjacentVertices[i]));
                }
            }
        }
    }
    free_dllist(queue);
}

void DFS(JRB graph, int start, int stop, void(*func)(int)){
    /*
    Input:
        start: the first vertex to visit
        stop: the vertex to be visited at the end, if stop = -1, all the vertices may be visited
        func: a pointer to the function that process on the visited vertices
    */

   int visited[100];

    JRB vertex = NULL;
    Dllist stack = new_dllist();

    jrb_traverse(vertex, graph) visited[jval_i(vertex->key)] = 0;
    
    dll_append(stack, new_jval_i(start));

    while(!dll_empty(stack)){
        // pop stack
        Dllist node = dll_last(stack);
        int v = jval_i(node->val);
        dll_delete_node(node);

        if(!visited[v]){
            func(v);
            visited[v] = 1;

            if(v == stop) return;
            int adjacentVertices[100];
            int n = getAdjacentVertices(graph, v, adjacentVertices);

            for(int i=0; i<n; i++){
                if(!visited[adjacentVertices[i]]) dll_append(stack, new_jval_i(adjacentVertices[i]));
            }
        }
    }
    free_dllist(stack);
}

JRB createGraph(){
    return make_jrb();
}

int main(){
    JRB graph = createGraph();

    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 4, 6);

    printf("\nBFS: start from node 1 to 5: ");
    BFS(graph, 1, 5, printVertex);
    printf("\nBFS: start from node 1 to all: ");
    BFS(graph, 1, -1, printVertex);
    printf("\n");

    printf("\nDFS: start from node 1 to 5: ");
    DFS(graph, 1, 5, printVertex);
    printf("\nDFS: start from node 1 to all: ");
    DFS(graph, 1, -1, printVertex);
    printf("\n");

    dropGraph(graph);
    
    return 0;
}