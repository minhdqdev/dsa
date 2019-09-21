/*
This is the most basic version of quicksort. You can find it on GeekForGeeks.
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}

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

void printArray(int *arr, int size){
    printf("Array: ");
    for(int i=0; i<size; i++){
        printf("%d ", *(arr+i));
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