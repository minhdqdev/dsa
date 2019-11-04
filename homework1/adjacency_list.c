/*
Adjacency List is usually preferred, because it provides a compact way 
to represent sparse graphs - those for which |E| is much less than |V|^2

Implement Adjacency List using Red Black Tree

Dang Quang Minh (minh.dq176823@sis.hust.edu.vn)
*/

#include "libfdr/jrb.h"
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

    if(node != NULL){
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

// int main(){
//     JRB graph = make_jrb();

//     addEdge(graph, 2, 3);

//     addEdge(graph, 1, 2);
//     addEdge(graph, 1, 3);
//     addEdge(graph, 1, 6);

//     printf("1 and 6: %d\n", adjacent(graph, 1, 6));
//     printf("1 and 5: %d\n", adjacent(graph, 1, 5));

//     int output[100];
//     int n = getAdjacentVertices(graph, 1, output);

//     if(n == 0) printf("No adjacent vertices of node 1\n");
//     else {
//         printf("Adjacent vertices of node 1: ");
//         for(int i=0; i<n; i++) printf("%5d", output[i]);
//         printf("\n");
//     }

//     n = getAdjacentVertices(graph, 2, output);

//     if(n == 0) printf("No adjacent vertices of node 2\n");
//     else {
//         printf("Adjacent vertices of node 2: ");
//         for(int i=0; i<n; i++) printf("%5d", output[i]);
//         printf("\n");
//     }

//     n = getAdjacentVertices(graph, 7, output);

//     if(n == 0) printf("No adjacent vertices of node 7\n");
//     else {
//         printf("Adjacent vertices of node 7: ");
//         for(int i=0; i<n; i++) printf("%5d", output[i]);
//         printf("\n");
//     }

//     if(jrb_find_int(graph, 1)){
//         printf("Graph is not free yet!\n");
//     }

//     dropGraph(graph);

//     if(jrb_find_int(graph, 1)){
//         printf("Graph is not free!\n");
//     }

//     return 0;
// }