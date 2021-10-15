#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"

void exch(void *buf, size_t size, int i, int j){   
    void *temp = malloc(sizeof(*buf));
    memcpy(temp, buf+i*sizeof(*buf), sizeof(*buf));
    memcpy(buf+i*sizeof(*buf), buf+j*sizeof(*buf), sizeof(*buf));
    memcpy(buf+j*sizeof(*buf), temp, sizeof(*buf));
    free(temp);  
}

int main(){
    int a[] = {1,2,3};

    for(int i=0; i<3; i++){
        printf("%p - %d\n", a+i, *(a+i));
    }
    

    // exch(a, sizeof(int), 0, 2);

    
    for(int i=0; i<3; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    Jval g = new_jval_i(5);

    return 0;
}