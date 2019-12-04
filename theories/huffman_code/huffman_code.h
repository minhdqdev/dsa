#ifndef _HUFFMAN_CODE_H_
#define _HUFFMAN_CODE_H_

#include <stdlib.h>
#include "libfdr/jrb.h"

typedef struct {
    Graph graph;
    JRB root;
} HuffmanTree;

typedef struct {
    int size;
    char bits[20];
} Coding;

Coding huffmanTable[256];

HuffmanTree makeHuffman(char *buffer, int size);

void createHuffmanTable(HuffmanTree htree, Coding *htable);

void compress(char *buffer, int size, char *huffman, int *nbit);

void addHuffmanChar(char *ch, Coding *htable, char *huffman, int *nbit);

#endif