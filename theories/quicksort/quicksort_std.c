/*
Declare a pointer to a function:
int (*pf)(int);
*/

#include <stdio.h>
#include <stdlib.h>

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

void printArray(int *arr, int size){
    printf("Array: ");
    for(int i=0; i<size; i++){
        printf("%d ", *(arr+i));
    }
    printf("\n");    
}

// return -1 if not found
int search( void* buf, int size, int l, int r, void * item, int (*compare)(void const*, void const*)) {
    if (r < l) return -1;
    int i = (l + r)/2;
    int res = compare( item, (char*)buf+(size*i) );
    if (res==0) return i;
    else if (res < 0) return search(buf, size, l, i-1, item, compare);
    else return search(buf, size, i+1, r, item, compare);
}

int main(){
    int n = 10;
    int a[10] = {9,7,3,5,1,0,2,6,4,8};

    qsort(a, n, sizeof(int), int_compare);

    printArray(a, n);

    int item = 12;

    int res = search(a, sizeof(int), 0, n-1, &item, int_compare);

    printf("Res: %d\n", res);

    qsort(a, n, sizeof(int), int_compare_reverse);

    printArray(a, n);


    return 0;
}