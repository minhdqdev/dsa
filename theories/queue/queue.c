#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct book {
	char id[10];
	char title[50];
	char author[20];
	int  published_year;
} Book;

typedef struct queue {
	int capacity;
	int front, rear;
	Book storage[MAX];
} Queue;

Queue* createQueue(int capacity){
	Queue *new_queue = (Queue*)malloc(sizeof(Queue));

	new_queue->capacity = capacity;
	new_queue->front = 0;
	new_queue->rear = -1;

	return new_queue;
}

int isEmpty(Queue *q){
	return q->rear == -1;
}

int isFull(Queue *q){
	return q->rear == q->capacity - 1;
}

void enqueue(Queue *q, Book b){
	if(!isFull(q)){
		q->rear++;
		q->storage[q->rear] = b;
		
	}	
	else printf("Queue  is full!\n");
}

Book dequeue(Queue *q){
	if(!isEmpty(q)){
		Book poped = q->storage[q->front];
		if(q->rear > 0){
			for(int i=0; i<=q->rear; i++){
				q->storage[i] = q->storage[i+1];
			}
		}
		q->rear--;

		return poped;
	}
	else printf("Queue is empty!\n");
}

Book frontQueue(Queue *q){
	if(!isEmpty(q)) return q->storage[q->front];

}

void printQueue(Queue *q){
	printf("Queue's Storage: {\n");
	for(int i=0; i<=q->rear; i++){
		printf("\t%d: %s - %s - %s - %d\n", i, q->storage[i].id, q->storage[i].title, q->storage[i].author, q->storage[i].published_year);
	}
	printf("}\n");
}

int main(){
	Queue *q = createQueue(3);

	Book b1 = {"S001", "DSA", "Minh", 2019};
	Book b2 = {"S002", "ABC", "Loc", 2019};
	Book b3 = {"S003", "XYZ", "Diep", 2018};

	enqueue(q,b1);
	enqueue(q,b2);
	enqueue(q,b3);
	enqueue(q,b3);

	printQueue(q);

	dequeue(q);
	dequeue(q);
	dequeue(q);
	dequeue(q);

	printQueue(q);

	Book b4 = frontQueue(q);

	printf("\t: %s - %s - %s - %d\n", b4.id, b4.title, b4.author, b4.published_year);

	printQueue(q);

	return 0;
}