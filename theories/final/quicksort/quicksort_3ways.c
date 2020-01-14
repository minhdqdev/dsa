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


int int_compare(void const *x, void const *y){
    int m, n;
    m = *((int*)x);
    n = *((int*)y);
    if(m == n) return 0;
    return m > n ? 1 : -1;
}

int int_compare_reverse(void const *x, void const *y){
    int m, n;
    m = *((int*)x);
    n = *((int*)y);
    if(m == n) return 0;
    return m > n ? -1 : 1;
}

void quickSort3Ways(int a[], int l, int r){
    if(r <= l) return;

    int i, j;

    partition3(a, l, r, &i, &j);

    quickSort3Ways(a, l, j);
    quickSort3Ways(a, i, r);
}

int main(){
    srand(time(NULL));

    // int n = pow(10, 5);
    int n = 20099;
    int a[n];
    int b[n];

    for(int i=0; i<n; i++){
        a[i] = rand();
        b[i] = rand() / 2;
    }

    // memcpy(a, b, sizeof(b));

    clock_t t = clock();
    quickSort3Ways(a, 0, n-1);
    t = clock() - t;
    printf("Elapsed: %lf - random elems\n", ((double)t)/CLOCKS_PER_SEC);
    
    t = clock();
    quickSort3Ways(b, 0, n-1);
    t = clock() - t;
    printf("Elapsed: %lf - duplicated elems\n", ((double)t)/CLOCKS_PER_SEC);
    

    // COMPARE 2WAYS VS 3WAYS RANDOM ELEMENTS
    for(int i=0; i<n; i++){
        a[i] = rand();
        b[i] = a[i];
    }
    
    t = clock();
    qsort(a, n, sizeof(int), int_compare);
    t = clock() - t;
    printf("Elapsed: %lf - 2 ways quicksort\n", ((double)t/CLOCKS_PER_SEC));

    t = clock();
    quickSort3Ways(b, 0, n-1);
    t = clock() - t;
    printf("Elapsed: %lf - 3 ways quicksort\n", ((double)t)/CLOCKS_PER_SEC);

    // COMPARE 2WAYS VS 3WAYS DUPLICATED ELEMENTS
    for(int i=0; i<n; i++){
        a[i] = rand() / 4;
        b[i] = a[i];
    }
    
    t = clock();
    qsort(a, n, sizeof(int), int_compare);
    t = clock() - t;
    printf("Elapsed: %lf - 2 ways quicksort\n", ((double)t/CLOCKS_PER_SEC));

    t = clock();
    quickSort3Ways(b, 0, n-1);
    t = clock() - t;
    printf("Elapsed: %lf - 3 ways quicksort\n", ((double)t)/CLOCKS_PER_SEC);


    return 0;
}