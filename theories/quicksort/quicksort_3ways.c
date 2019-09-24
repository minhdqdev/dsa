#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

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

void partition(int a[], int l, int r, int *i, int *j){
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

    partition(a, l, r, &i, &j);

    quickSort3Ways(a, l, j);
    quickSort3Ways(a, i, r);
}

int main(){
    srand(time(NULL));

    int n = pow(10, 4);
    int a[n];
    int b[n];

    for(int i=0; i<n; i++){
        a[i] = rand();
        b[i] = rand();
    }

    // memcpy(a, b, sizeof(b));

    clock_t t = clock();
    // quickSort3Ways(a, 0, n-1);
    // t = clock() - t;
    // printf("Elapsed: %lf - random elems\n", ((double)t)/CLOCKS_PER_SEC);
    
    t = clock();
    quickSort3Ways(b, 0, n-1);
    t = clock() - t;
    printf("Elapsed: %lf - duplicated elems\n", ((double)t)/CLOCKS_PER_SEC);
    
    return 0;
}