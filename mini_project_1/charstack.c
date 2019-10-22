#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct charStack{
    char *array;
    int top;
    int capacity;
} CharStack;

CharStack *createCharStack(int capacity){
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Stack is full when top is equal to the last index 
int isFull(CharStack* stack) 
{ 
    return stack->top == stack->capacity - 1; 
} 
  
// Stack is empty when top is equal to -1 
int isEmpty(CharStack* stack) 
{ 
    return stack->top == -1; 
} 
  
// Function to add an item to stack.  It increases top by 1 
void push(CharStack* stack, int item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    // printf("%d pushed to stack\n", item); 
} 
  
void pushString(CharStack* stack, char *str){
    int i = 0;
    while(str[i] != '\0'){
        push(stack, str[i]);
        i++;
    }
}

void stackToString(CharStack* stack, char *result){
    memset(result, '\0', 50);
    memcpy(result, stack->array, sizeof(char) * (stack->top+1));
    result[stack->top+1] = '\0';
}

// Function to remove an item from stack.  It decreases top by 1 
int pop(CharStack* stack) 
{ 
    if (isEmpty(stack)) 
        return CHAR_MIN; 
    return stack->array[stack->top--]; 
} 
  
// Function to return the top from stack without removing it 
int peek(CharStack* stack) 
{ 
    if (isEmpty(stack))
        return CHAR_MIN; 
    return stack->array[stack->top]; 
} 

void printStack(CharStack* stack){
    printf("Stack: [-");

    for(int i=0; i<=stack->top; i++){
        printf("%c", *(stack->array+i));
    }
    printf("-]\n");
}