#include <stdio.h>
#include "libfdr/dllist.h"
#include "huffman_code.h"

HuffmanTree makeHuffman(char *buffer, int size){
    Dllist pq = new_dllist();

    int i = 0;
    while(buffer[i] != '\0'){
        Dllist temp;

        JRB node = make_jrb();
        node->key = new_jval_c(buffer[i]);
        node->val = new_jval_i(1);

        dll_append(pq, )

        dll_traverse(temp, pq){
            if( ((JRB)dll_val(temp))->key == buffer[i] ){

            }
        }


        
    }
}