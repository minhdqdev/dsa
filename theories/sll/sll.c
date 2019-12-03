#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct book {
	char id[10];
	char title[50];
	char author[20];
	int  published_year;
} Book;

typedef struct node {
	Book data;
	struct node *next;
} Node;

Node* createNode(){
	return (Node*)malloc(sizeof(Node));
}

void printList(Node *n){ //traverse a SLL
	printf("SLL's Storage: {\n");
	int i = 0;
	while(n != NULL){
		printf("\t%d: %s - %s - %s - %d\n", i, n->data.id, n->data.title, n->data.author, n->data.published_year);
		n = n->next;
		i++;
	}
	printf("}\n");
}

void insertFront(Node **root, Book b){
	Node *new_node = createNode();

	new_node->data = b;
	new_node->next = *root;
	*root = new_node;
}

void insertAfter(Node **prev_node, Book b){
	if(*prev_node == NULL){
		insertFront(prev_node, b);
	}
	else{
		Node *new_node = createNode();

		new_node->data = b;
		new_node->next = (*prev_node)->next;
		(*prev_node)->next = new_node;
	}
}

void insertTail(Node **head, Book b){
	if(*head == NULL){
		insertFront(head, b);
	}
	else{
		// Find the last node
		Node *last = *head;

		while(last->next != NULL){
			last = last->next;
		}

		Node *new_node = createNode();
		new_node->data = b;
		new_node->next = NULL;

		last->next = new_node;
	}
}

Book popFront(Node **root){
	if(*root != NULL){
		Node *cur = *root;
		Book poped = cur->data;
		*root = (*root)->next;
		free(cur);

		return poped;
	}
	else printf("SLL is empty!\n");
}

Book popTail(Node **root){
	if(*root != NULL){
		Node *tail = *root;

		while(tail->next != NULL){
			tail = tail->next;
		}

		if(tail == *root){
			Book poped = (*root)->data;
			*root = NULL;
		}
		else{
			Node *before_tail = *root;

			while(before_tail->next != tail){
				before_tail = before_tail->next;
			}
			before_tail->next = NULL;
			free(tail);
		}
	}
	else printf("SLL is empty!\n");
}

void deleteNodeByKey(Node **head, char* key){
	Node *temp = *head;
	Node *prev = NULL;

	if(strcmp((*head)->data.id, key) == 0){
		*head = (*head)->next;
		free(temp);
	}
	else{
		while(temp != NULL && strcmp(temp->data.id, key) != 0){
			prev = temp;
			temp = temp->next;
		}

		if(temp == NULL) printf("There is no matched node to be delete!\n");
		else{
			prev->next = temp->next;

			free(temp);
		}
		
	}
}

void freeList(Node **head){
	Node *temp = *head;
	Node *prev = NULL;

	while(temp != NULL){
		prev = temp;
		temp = temp->next;
		free(prev);
	}

	*head = NULL;
	printf("SLL is deleted!\n");
}

int main(){
	

	Book b1 = {"S001", "DSA", "Minh", 2019};
	Book b2 = {"S002", "ABC", "Loc", 2019};
	Book b3 = {"S003", "XYZ", "Diep", 2018};

	Node *head = NULL;
	insertTail(&head, b1);
	printList(head);
	insertTail(&head, b2);
	printList(head);
	insertTail(&head, b3);
	printList(head);
	popFront(&head);
	popFront(&head);
	popFront(&head);
	popFront(&head);

	insertAfter(&head, b1);
	printList(head);
	insertAfter(&head, b2);
	printList(head);
	insertAfter(&head, b3);
	printList(head);


	freeList(&head);

	printList(head);
	return 0;
}