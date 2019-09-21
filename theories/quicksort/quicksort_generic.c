#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// generic swap
void swap_gen(void *a, void *b, size_t size){
    void *c = malloc(size);
    memcpy(c, a, size);
    memcpy(a, b, size);
    memcpy(b, c, size);
    free(c);
}

//TODO: Similarly, we have the exchange function for two item in an array.

int int_compare(void *a, void *b) { return (*(int*)a - *(int*)b); }


int partition(int arr[], int left, int right){
    int pivot = arr[left];

    int i = left;

    for(int j=left+1; j<=right; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i], &arr[left]);
    return i;
}

int quickSort(int arr[], int left, int right){
    if(left < right){
        int pivot = partition(arr, left, right);

        quickSort(arr, left, pivot-1);
        quickSort(arr, pivot+1, right);
    }
    
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