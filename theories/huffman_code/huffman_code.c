#include <stdio.h>
#include <string.h>
#include "libfdr/dllist.h"
#include "libfdr/jrb.h"

typedef struct{
    JRB vertices;
    JRB edges;
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

void addPQueue(Dllist pq, int key, int priority){
    if(dll_empty(pq) || jval_i(((JRB)jval_v(dll_last(pq)->val))->key) < priority){ // pq is empty or priority is the new highest value
        JRB n = make_jrb();
        n->key = new_jval_i(priority);
        n->val = new_jval_i(key);
        dll_append(pq, new_jval_v(n));
        return;
    }

    Dllist node = pq->flink;
    while(node != pq){
        if(jval_i(((JRB)jval_v(node->val))->key) >= priority){
            JRB n = make_jrb();
            n->key = new_jval_i(priority);
            n->val = new_jval_i(key);
            dll_insert_b(node, new_jval_v(n));
            return;
        }
        node = node->flink;
    }
}

void addPQueueJRB(Dllist pq, JRB node){
    if(dll_empty(pq) || jval_i(((JRB)jval_v(dll_last(pq)->val))->key) < jval_i(node->val)){
        dll_append(pq, new_jval_v(node));
        return;
    }

    Dllist next = pq->flink;
    while
}

JRB popPQueue(Dllist pq){
    JRB value = (JRB)jval_v(dll_first(pq)->val);
    dll_delete_node(dll_first(pq));
    return value;
}

void printPQueue(Dllist pq){
    Dllist node = dll_first(pq);
    printf("PQ: \n");
    while(node != pq){
        printf("%c : %d\n", jval_i(((JRB)jval_v(node->val))->val), jval_i(((JRB)jval_v(node->val))->key));
        node = node->flink;
    }
    printf("\n");
}

int sizePQueue(Dllist pq){
    Dllist node = pq->flink;

    int size = 0;

    while(node != pq){
        size++;
        node = node->flink;
    }

    return size;
}


typedef struct{
    Graph graph;
    JRB root;
} HuffmanTree;

typedef struct{
    int size;
    char bits[20];
} Coding;

HuffmanTree makeHuffman(char *buffer, int size){

}

void createHuffmanTable(HuffmanTree htree, Coding *htable){

}

void addHuffmanChar(char *ch, Coding *htable, char* huffman, int *nbit){


}

void compress(char *buffer, int size, char *huffman, int *nbit){
    // Create Priority Queue
    Dllist pq = new_dllist(); 

    int freq[256];
    for(int i=0 ;i<256; i++) freq[i] = 0;
    for(int i=0; i<size; i++) freq[buffer[i]] += 1;
    for(int i=0; i<256; i++){
        if(freq[i] > 0){
            addPQueue(pq, i, freq[i]);
        }
    }
    printPQueue(pq);

    while(sizePQueue(pq) >= 2){
        JRB node1 = popPQueue(pq);
        JRB node2 = popPQueue(pq);

        JRB mergedNode = make_jrb();
        mergedNode->key = new_jval_i(jval_i(node1->key) + jval_i(node2->key));
        mergedNode->val = new_jval_i(-1);


        // Node *mergedNode = newNode(-1, node1->priority + node2->priority);

    }

    Coding huffmanTable[256];

    free_dllist(pq);
}

int main(){
    char buffer[] = "Eerie eyes seen near lake.";
    int size = strlen(buffer);

    char huffman[1000];
    int nbit;

    compress(buffer, size, huffman, &nbit);


    return 0;
}
