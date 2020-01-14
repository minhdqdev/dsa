#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jrb.h"

// generic swap
void swap_gen(void *a, void *b, size_t size){
    void *c = malloc(size);
    memcpy(c, a, size);
    memcpy(a, b, size);
    memcpy(b, c, size);
    free(c);
}

void exch(void *buf, int size, int i, int j){
    void *temp = malloc(size);
    memcpy(temp, buf+i, size);
    memcpy(buf+i, buf+j, size);
    memcpy(buf+j, temp, size);
    free(temp);
}

void sort_gen(Jval a[], int l, int r, int (*compare)(Jval*, Jval*)){

}

int search_gen(Jval a[], int l, int r, Jval item, int (*compare)(Jval*, Jval*)){


}

int compare_i(Jval* a, Jval* b) {
    if ( jval_i(*a)==jval_i(*b) ) return 0;
    if ( jval_i(*a) < jval_i(*b) ) return -1;
    else return 1;
}
void sort_i (Jval a[], int l, int r) {
    sort_gen(a, l, r, compare_i);
}
int search_i (Jval a[], int l, int r, int x) {
    return search_gen(a, l, r, new_jval_i(x), compare_i);
}
Jval* create_array_i (int n) {
    Jval * array = (Jval *) malloc(sizeof(Jval)*n);
    for (int i=0; i<n; i++) array[i] = new_jval_i( rand() );
    return array;
}

void printArray(int arr[], int size){
    printf("Array: ");
    for(int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");    
}

int main(){
    int a[] = {9,5,7,1,2,0,3,4,8,6};
    int n = 10;
    printArray(a, n);
    quickSort(a, 0, n-1);

    printArray(a, n);
    return 0;
}