#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int DEFAULT_SIZE = 16;

typedef struct pi {
    int *numbers;
    int n;
    int total;
    int size;
    int *bin;
} PI;

PI *createNewPI(int n, int number){
    PI *newPI = (PI*)malloc(sizeof(PI));
    newPI->size = DEFAULT_SIZE;
    newPI->total = 1;
    newPI->n = n;
    newPI->numbers = (int*)malloc(sizeof(int) * newPI->size);
    newPI->bin = (int*)malloc(sizeof(int) * n);
    toBin(number, newPI->bin, n);

    return newPI;
}

typedef struct node {
    PI *pi;

    struct node *next;
} Node;

Node *createNewNode(int n, int number){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->pi = createNewPI(n, number);
    newNode->next = NULL;

    return newNode;
}

void freePI(PI *pi){
    free(pi->numbers);
    free(pi->bin);
    free(pi);
}

void freeNode(Node *node){
    freePI(node->pi);
    free(node);
}

void appendList(Node* head, Node *node){
    Node* cur = head;
    if(cur == NULL) head = node;

    while(cur->next == NULL) cur = cur->next;
    cur->next = node;
}

void toBin(int number, int a[], int n){
    for(int i=n-1; i>=0; i--){
        if(number >= pow(2, i)){
            a[n-1-i] = 1;
            number -= pow(2, i);
        }
        else a[n-1-i] = 0;
    }
}

void printBin(int a[], int n){
    for(int i=0; i<n; i++){
        printf("%d", a[i]);
    }
}

int countOnes(int bin[], int n){
    int count = 0;
    for(int i=0; i<n; i++) if(bin[i]) count++;
    return count;
}

// void printGroup(Node* group, int n){
//     for
// }

int main(){
    int n, m, d;

    printf("Input the number of variables: ");
    scanf("%d", &n);

    printf("Input the number of minterms and minterms: ");
    scanf("%d", &m);

    int mList[m];
    for(int i=0; i<m; i++) scanf("%d", &mList[i]);

    printf("Input the number of don't cares and don't cares: ");
    scanf("%d", &d);
    
    int dList[d];
    for(int i=0; i<d; i++) scanf("%d", &dList[i]);

    int bin[n];
    for(int i=0; i<m; i++){
        toBin(mList[i], bin, n);
        printf("%d - ", mList[i]);
        printBin(bin, n);
        printf("\n");
    }

    Node *group[n+1];

    for(int i=0; i<m; i++){
        PI *newNode = createNewNode(n, mList[i]);
        int count = countOnes(newNode->bin, newNode->n);

        appendList(group[count], newNode);
    }

    return 0;
}