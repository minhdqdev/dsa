#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct queue{
    void* data[MAX_SIZE];    
    int top;
    int size;
} Queue;

Queue* newQueue(int size){
    Queue* new = (Queue*)malloc(sizeof(Queue));
    new->top = -1;
    new->size = MAX_SIZE;
}

void appendQueue(Queue* q, void* pointer){
    if(!queueFull){
        q->data[++(q->top)] = pointer;
    }
}

void* popQueue(Queue *q){
    if(!queueEmpty){
        void* res = q->data[0];

        for(int i=0; i<q->top; i++){
            q->data[i] = q->data[i+1];
        }
        q->data[q->top--] = NULL;
    }

}

int queueFull(Queue* q){
    return(q->top == q->size-1);
}

int queueEmpty(Queue *q){
    return(q->top == -1);
}

void freeQueue(Queue * q){

}