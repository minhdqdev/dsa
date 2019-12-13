#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/dllist.h"

void printList(Dllist list){
    Dllist node;
    printf("List: ");
    dll_traverse(node, list){
        printf("%4d", jval_i(node->val));
    }
    printf("\n");
}

typedef struct{
    int key;
    int priority;
} Node;

Node* newNode(int key, int priority){
    Node* new = (Node*)malloc(sizeof(new));
    new->key = key;
    new->priority = priority;

    return new;
}

void addPQueue(Dllist pq, int key, int priority){
    if(dll_empty(pq) || ((Node*)jval_v(dll_last(pq)->val))->priority < priority){ // pq is empty or priority is the new highest value

        dll_append(pq, new_jval_v(newNode(key, priority)));
        return;
    }

    Dllist node = pq->flink;
    while(node != pq){
        if(((Node*)jval_v(node->val))->priority >= priority){
            dll_insert_b(node, new_jval_v(newNode(key, priority)));
            return;
        }
        node = node->flink;
    }
}

Node* popPQueue(Dllist pq){
    Node* value = (Node*)jval_v(dll_first(pq)->val);
    dll_delete_node(dll_first(pq));
    return value;
}

void printPQueue(Dllist pq){
    Dllist node = dll_first(pq);
    printf("PQ: \n");
    while(node != pq){
        printf("%c : %d\n", ((Node*)jval_v(node->val))->key, ((Node*)jval_v(node->val))->priority);
        node = node->flink;
    }
    printf("\n");
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
    // popPQueue(pq);
    // popPQueue(pq);
    // printPQueue(pq);


    while(!dll_empty(pq)){
        Node *node1 = popPQueue(pq);
        Node *node2 = popPQueue(pq);
    }

    Coding huffmanTable[256];

    free_dllist(pq);
}

int main(){
    // Dllist list = new_dllist();

    // dll_append(list, new_jval_i(1));
    // dll_append(list, new_jval_i(3));
    // dll_append(list, new_jval_i(4));

    // printList(list);

    // printf("%4d\n", jval_i(dll_first(list)->val));

    // dll_delete_node(dll_first(list));

    // printList(list);

    // free_dllist(list);

    char buffer[1000] = "Eerie eyes seen near lake.";
    int size = strlen(buffer);

    char huffman[1000];
    int nbit;

    compress(buffer, size, huffman, &nbit);

    return 0;
}