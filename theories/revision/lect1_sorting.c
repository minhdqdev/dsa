#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}

void printArray(int *arr, int size){
    printf("Array: ");
    for(int i=0; i<size; i++){
        printf("%d ", *(arr+i));
    }
    printf("\n");    
}

// 2-way partitioning quicksort
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

// 3-way partitioning quicksort
void partition3(int a[], int l, int r, int *i, int *j){
    *i = l-1;
    *j = r;
    int p = l-1, q = r;
    int v = a[r];

    while(1){
        while(a[++*i] < v);
    
        while(v < a[--*j]) if (*j == l) break;

        if(*i >= *j) break;

        swap(&a[*i], &a[*j]);

        if(a[*i] == v){
            p++;
            swap(&a[*j], &a[q]);
        }
    }

    swap(&a[*i], &a[r]);

    *j = *i-1;

    for(int k=l; k<p; k++, *j--) swap(&a[k], &a[*j]);

    *i++;

    for(int k=r-1; k>q; k--, *i++) swap(&a[*i], &a[k]);
}

void quickSort3Ways(int a[], int l, int r){
    if(r <= l) return;

    int i, j;

    partition3(a, l, r, &i, &j);

    quickSort3Ways(a, l, j);
    quickSort3Ways(a, i, r);
}

void quiz1(){
    // Quiz 1
    srand(time(NULL));
    int n = 10;
    int c[n];
    int b[n];
    for(int i=0; i<n; i++){
        c[i] = rand() % 11;
        b[i] = rand() % 11;
    }

    clock_t t = clock();

    t = clock();
    quickSort(c, 0, n-1);
    t = clock() - t;

    printf("2-ways - Elasped: %lf\n", ((double)t/CLOCKS_PER_SEC));

    printArray(c, n);

    // Error: segmentation fault (core dumped)
    // t = clock();
    // quickSort3Ways(b, 0, n-1);
    // t = clock() - t;

    // printf("3-ways - Elasped: %lf\n", ((double)t/CLOCKS_PER_SEC));

    
}

int main(){
    quiz1();


    return 0;
}