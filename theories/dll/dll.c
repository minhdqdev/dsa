#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int data;
	struct node* prev;
	struct node* next;
} Node;

Node* newNode(){
	return (Node*)malloc(sizeof(Node));
}

void printList(Node *root){
	Node *cur = root;

	while(cur != NULL){
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

void printListReversed(Node* tail){
	Node *cur = tail;

	while(cur != NULL){
		printf("%d ", cur->data);
		cur = cur->prev;
	}
	printf("\n");
}

void insertFront(Node **root, int data){
	Node *new_node = newNode();
	new_node->data = data;

	new_node->next = *root;
	new_node->prev = NULL;

	(*root)->prev = new_node;


	*root = new_node;
}

void insertAfter(Node *prev_node, int data){
	Node *new_node = newNode();
	new_node->data = data;
	Node *next_node = prev_node->next;

	if(prev_node->next != NULL){
		next_node->prev = new_node;
		new_node->next = prev_node->next;
	}

	new_node->prev = prev_node;
	prev_node->next = new_node;
	
}

int main(){
	Node *head = newNode();
	Node *second = newNode();
	Node *third = newNode();

	head->data = 1;
	head->prev = NULL;
	head->next = second;

	second->data = 2;
	second->prev = head;
	second->next = third;

	third->data = 3;
	third->prev = second;
	third->next = NULL;

	insertFront(&head, 0);

	insertAfter(second, 5);

	printList(head);

	printListReversed(third);
	return 0;
}

