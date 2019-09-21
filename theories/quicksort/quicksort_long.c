/*
This is the long version of quicksort, which use long data type rather than integer data type.
This is useful for time benchmarking.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void swap(long *a, long *b){
    long c = *a;
    *a = *b;
    *b = c;
}

long partition(long arr[], long left, long right){
    long pivot = arr[left];

    long i = left;

    for(long j=left+1; j<=right; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i], &arr[left]);
    return i;
}

long quickSort(long arr[], long left, long right){
    if(left < right){
        long pivot = partition(arr, left, right);

        quickSort(arr, left, pivot-1);
        quickSort(arr, pivot+1, right);
    }
    
}

void printArray(long *arr, long size){
    printf("Array: ");
    for(long i=0; i<size; i++){
        printf("%ld ", *(arr+i));
    }
    printf("\n");    
}

int main(){
    srand(time(NULL));

    long n = pow(10, 5);
    long a[n];
    long b[n];

    for(int i=0; i<n; i++){
        a[i] = rand();
        b[i] = rand() % 21;
    }

    // printArray(a, n);
    clock_t t = clock();
    quickSort(a, 0, n-1);
    t = clock() - t;
    printf("Elapsed: %lf - random elems\n", ((double)t)/CLOCKS_PER_SEC);
    
    t = clock();
    quickSort(b, 0, n-1);
    t = clock() - t;
    printf("Elapsed: %lf - duplicated elems\n", ((double)t)/CLOCKS_PER_SEC);
    
    return 0;
}