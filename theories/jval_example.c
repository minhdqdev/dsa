/*
Jval is used for generic programming

*/
#include "libfdr/jrb.h"

int main(){
    Jval a, b; 
    a = new_jval_i(5);
    b = new_jval_f(3.14);

    printf("%d\n", jval_i(a));
    printf("%f\n", jval_f(b));

    return 0;
}