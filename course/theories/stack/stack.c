#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct book {
	char id[10];
	char title[50];
	char author[20];
	int  published_year;
} Book;

typedef struct stack {
	int top;
	int capacity;
	Book storage[MAX];
} Stack;

Stack* createStack(int capacity){
	Stack *new_stack = (Stack*)malloc(sizeof(Stack));
	new_stack->capacity = capacity;
	new_stack->top = -1;

	return new_stack;
}

int isEmpty(Stack *s){
	return s->top == -1;
}

int isFull(Stack *s){
	return s->top == s->capacity-1;
}

void pushStack(Stack *s, Book b){
	if(!isFull(s)){
		s->top++;
		s->storage[s->top] = b;
	}
	else printf("Stack is full!\n");
}

Book popStack(Stack *s){
	if(!isEmpty(s)){
		Book poped = s->storage[s->top];
		s->top--;
		return poped;
	}
	else{
		printf("Stack is empty!\n");
	}
}

Book topStack(Stack *s){
	if(!isEmpty(s)){
		return s->storage[s->top];
	}
}

void printStack(Stack *s){
	printf("Stack's Storage: {\n");
	for(int i=0; i<=s->top; i++){
		printf("\t%d: %s - %s - %s - %d\n", i, s->storage[i].id, s->storage[i].title, s->storage[i].author, s->storage[i].published_year);
	}
	printf("}\n");
}

void freeStack(Stack *s){
	free(s);
	printf("Free Stack!\n");
}

int main(){
	Stack *s = createStack(3);

	Book b1 = {"S001", "DSA", "Minh", 2019};
	Book b2 = {"S002", "ABC", "Loc", 2019};
	Book b3 = {"S003", "XYZ", "Diep", 2018};

	pushStack(s, b1);

	Book b4 = topStack(s);

	pushStack(s, b4);

	printStack(s);

	freeStack(s);

	return 0;
}