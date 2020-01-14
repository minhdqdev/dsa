// #include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

#define INFINITIVE_VALUE  10000000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, int letter);
int getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, int weight);
int getEdgeValue(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void dropGraph(Graph graph);

typedef struct {
   Graph graph;
   int rootID;
} HuffmanTree;

typedef Dllist PriorityQueue;

typedef struct {
	int size;
	char bits[20]; // maximum 20 bits, it is safe enough
} Coding;

typedef struct {
	int size;
	int * nodes;
} HuffmanTreeArray;

void add2Queue(PriorityQueue q, int graphnode, int frequence);
HuffmanTree makeHuffman(int fTable[]);
void createHuffmanTable(HuffmanTree htree, Coding htable[]);
void setBit(char* huffman, int nbit, int val);
int getBit(char* huffman, int nbit);
void addHuffmanChar(char ch, Coding htable[], char* huffman, int* nbit);
int compress(char* buffer, char*huffman, Coding htable[]);
void writeHuffmanTable(Coding htable[], FILE* f);
void compressFile(char* input, char*output);
void setRoot(int* cursor);
void goLeft(int* cursor);
void goRight(int* cursor);
HuffmanTreeArray makeHuffmanTreeArray(Coding htable[]);
void destroyHuffmanTreeArray(HuffmanTreeArray htree);
int decompress(char * huffman, int nbit, Coding htable[], char * buffer);
void decompressFile(char *input, char *output);

int main()
{
   char buffer[1000] = "fdfdfdfgjkfjkgrutrtrtkgfkgjjfdfsdiruiedfffdffgffg";
   char huffman[1000];
   Coding htable[256];
   int nbit, bytes;
   nbit = compress(buffer, huffman, htable);
   bytes = decompress(huffman, nbit, htable, buffer);
   buffer[bytes] = '\0';
   printf("%s\n", buffer);
   compressFile("hello.txt", "huffman.dat");
   decompressFile("huffman.dat", "hello_new.txt");
}

Graph createGraph()
{
   Graph g; 
   g.edges = make_jrb();  
   g.vertices = make_jrb();  
   return g;
}

void addVertex(Graph g, int id, int letter)
{
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) // only add new vertex 
         jrb_insert_int(g.vertices, id, new_jval_i(letter));            
}

int getVertex(Graph g, int id)
{
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) 
        return 0;
     else                
        return jval_i(node->val);
}     

void addEdge(Graph graph, int v1, int v2, int weight)
{
     JRB node, tree;
     if (getEdgeValue(graph, v1, v2)==INFINITIVE_VALUE)
     {
        node = jrb_find_int(graph.edges, v1);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        } else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_i(weight));
     }
}

int getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node==NULL)
       return INFINITIVE_VALUE;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node==NULL)
       return INFINITIVE_VALUE;
    else
       return jval_i(node->val);       
}

int indegree (Graph graph, int v, int* output)
{
    JRB tree, node;
    int total = 0;   
    jrb_traverse(node, graph.edges)
    {
       tree = (JRB) jval_v(node->val);
       if (jrb_find_int(tree, v))
       {
          output[total] = jval_i(node->key);
          total++;
       }                
    }
    return total;   
}

int outdegree (Graph graph, int v, int* output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;   
    jrb_traverse(node, tree)
    {
       output[total] = jval_i(node->key);
       total++;                
    }
    return total;   
}

void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}



void add2Queue(PriorityQueue q, int graphnode, int frequence) {
	Dllist node = dll_first(q);
	while (node!=q) {
		// printf("Node %d %d\n", jval_iarray(dll_val(node))[0], jval_iarray(dll_val(node))[1] );
		if ( frequence <= jval_iarray(dll_val(node))[1] ) break;
		node =  dll_next(node);
	}
	if ( node==q ) {
		// printf("Node nil\n");
		dll_append(q, new_jval_iarray(graphnode, frequence));
	} else {
		// printf("Before %d %d\n", jval_iarray(dll_val(node))[0], jval_iarray(dll_val(node))[1] );
		dll_insert_b(node, new_jval_iarray(graphnode, frequence));	
	}
}

HuffmanTree makeHuffman(int fTable[]) {
	int lastNodeID = 0;
	HuffmanTree	hTree;
	int i;
	Dllist n1, n2;

	PriorityQueue queue = new_dllist();
	hTree.graph = createGraph();

	for (i=0; i<256; i++)
		if (fTable[i]) {
			// make new graphNode to add to the priority queue
			lastNodeID++;
			addVertex(hTree.graph, lastNodeID, i);
			add2Queue(queue, lastNodeID, fTable[i]);
			// printf("last %d %c %d\n", lastNodeID, i, fTable[i]);
		}
	
/*	for (n1 = dll_first(queue); n1!=queue; n1=dll_next(n1))
	{
		printf("%d %d\n", jval_iarray(dll_val(n1))[0], jval_iarray(dll_val(n1))[1]);
	}
*/	
	// regroup nodes in priority queue
	for (;;)
	{
		n1 = dll_first(queue);
		if ( n1==queue ) break;
		n2 = dll_next(n1);
		if ( n2==queue ) break;
		// add new node in the graph
		lastNodeID++;
		addVertex(hTree.graph, lastNodeID, -1);
		addEdge(hTree.graph, lastNodeID, jval_iarray(dll_val(n1))[0], 0); 
		addEdge(hTree.graph, lastNodeID, jval_iarray(dll_val(n2))[0], 1); 
		//printf("last %d\n", lastNodeID);
		// modify the queue
		dll_delete_node(n1);
		dll_delete_node(n2);
		add2Queue(queue, lastNodeID, jval_iarray(dll_val(n1))[1]+jval_iarray(dll_val(n2))[1] );
	}
	n1 = dll_first(queue);
	if ( n1==queue ) 
		hTree.rootID = 0;
	else
		hTree.rootID = jval_iarray(dll_val(n1))[0];	
	
	free_dllist(queue);

	return hTree;
}

void getCode(int node, Graph g, int len, char code[], Coding htable[]) 
{
	int ch, k, i;
	int output[10];
	ch = getVertex(g, node);
	if (ch != -1) {
		htable[ch].size = len;
		memcpy(htable[ch].bits, code, len);	
	} else {
		k = outdegree(g, node, output);
		for (i=0; i<k; i++) {
			code[len] = getEdgeValue(g, node, output[i]);
			getCode(output[i], g, len+1, code, htable);
		}
	}
}

void createHuffmanTable(HuffmanTree htree, Coding htable[]) {
	int i;
	char code[20];
	for (i=0; i<256; i++) {
		htable[i].size=0;
	}
	if (htree.rootID == 0) return;
	getCode(htree.rootID, htree.graph, 0, code, htable); 
}

void setBit(char* huffman, int nbit, int val) {
	int i, byte, bit;
	byte = nbit/8;
	bit = nbit%8;
	if (val==0) {
		huffman[byte] &= ~(1 << bit);
	} else {
		huffman[byte] |= (1 << bit);
	}
}

int getBit(char* huffman, int nbit) {
	int i, byte, bit;
	byte = nbit/8;
	bit = nbit%8;
	i =	huffman[byte] & (1 << bit);
	return i!=0;
}

void addHuffmanChar(char ch, Coding htable[], char* huffman, int* nbit) {
	int i;
	for (i=0; i<htable[ch].size; i++) {
		setBit(huffman, *nbit, htable[ch].bits[i]);
		(*nbit)++;
	}
}

// return number of bits
int compress(char* buffer, char*huffman, Coding htable[]) {
	HuffmanTree htree;
	int i, k, n, nbit;
	
	int fTable[256] = {} ;
	unsigned int ch;
	
	for (i=0; i<strlen(buffer); i++) {
		ch = buffer[i];
		fTable[ch]++;
	}

	htree = makeHuffman (fTable);
	createHuffmanTable(htree, htable);
	printf("Huffman Table Code:\n");
	for (i=0; i<256; i++) {
		if (htable[i].size > 0) {
			printf ("Char %c ", i);
			for (k=0; k<htable[i].size; k++)
			   printf ("%d", htable[i].bits[k]);
			printf ("\n");   
		}
	}
	
	printf("Original size: %ld bytes\n", strlen(buffer));
	printf("%s\n", buffer);
	// Compress
	n = strlen(buffer);
	nbit = 0;
	for (i=0; i<n; i++)
		addHuffmanChar(buffer[i], htable, huffman, &nbit);
	printf("Compressed size: %d bytes\n", (nbit/8)+1);
	for (i=0; i<nbit; i++)
		printf("%d", getBit(huffman, i));
	printf("\n");
	return nbit;
}

void writeHuffmanTable(Coding htable[], FILE* f) {
	int i, num=0, n, k;
	char buffer[10];
	num=0;
	for (i=0; i<256; i++) {
		if (htable[i].size > 0) {
			num++;  
		}
	}
	printf("Num of chars: %d\n", num);
	fwrite(&num, sizeof(int), 1, f);
	for (i=0; i<256; i++) {
		if (htable[i].size > 0) {
			fputc(i, f);
			fwrite(&htable[i].size, sizeof(int), 1, f);
			printf("%c: %d bits\n", i, htable[i].size);
			for (k=0; k<htable[i].size; k++)
				setBit(buffer, k, htable[i].bits[k]);
			n = htable[i].size/8;
			if (htable[i].size%8) n++;
			fwrite(buffer, n, 1, f);			  
		}
	}
}

void compressFile(char* input, char*output) {
	HuffmanTree htree;
	Coding htable[256] = {};
	int i, k, n, nbit, size;
	
	FILE* f1, *f2;

	int fTable[256] = {} ;
	
	char* huffman;
	
	f1 = fopen(input, "rb");
	if (f1==NULL) {
		perror("Can not open input file\n");
		exit(2);
	}
	
	size = 0;
	while ( (i=fgetc(f1)) != -1 ) {
		fTable[i]++;
		size++;
	}
	
	printf("Input: %d bytes\n", size);
	
	if (size==0) return;
	
	htree = makeHuffman (fTable);
	createHuffmanTable(htree, htable);
	
	f2 = fopen(output, "w+b");
	if (f2==NULL) {
		perror("Can not open output file\n");
		exit(2);
	}
	fwrite("HM", 2, 1, f2);
	writeHuffmanTable(htable, f2);
	
	fseek(f1, 0, SEEK_SET);
	nbit = 0;
	huffman = malloc(size);
	while ( (i=fgetc(f1)) != -1 ) {
		addHuffmanChar(i, htable, huffman, &nbit);
	}
	fwrite(&nbit, sizeof(int), 1, f2);
	n = nbit/8;
	if (nbit%8) n++;
	fwrite(huffman, n, 1, f2);
	free(huffman);
	printf("Compressed: %d bytes\n", n);
	
	fclose(f1);
	fclose(f2);
}

// typedef struct {
// 	int size;
// 	int * nodes;
// } HuffmanTreeArray;

void setRoot(int* cursor) {
	*cursor = 0;
}

void goLeft(int* cursor) {
	*cursor = 2*(*cursor) + 1;
}

void goRight(int* cursor) {
	*cursor = 2*(*cursor) + 2;
}

HuffmanTreeArray makeHuffmanTreeArray(Coding htable[]) 
{
	int i, k, maxlen, size, exp2, cursor;
	HuffmanTreeArray hArray;
	
	maxlen = 0;
	for (i=0; i<256; i++)
		if (htable[i].size > maxlen) maxlen = htable[i].size;
	size = 1;
	exp2 = 1;
	for (i=1; i<=maxlen; i++) {
		exp2 *= 2;	
		size += exp2;
	}
	hArray.size = size;
	hArray.nodes = malloc(hArray.size*sizeof(int));
	for (i=0; i<hArray.size; i++) hArray.nodes[i] = -1;
	for (i=0; i<256; i++) {
		setRoot(&cursor);
		if (htable[i].size) {
			for (k=0; k<htable[i].size; k++) {
				if (htable[i].bits[k]==0) goLeft(&cursor);
				else goRight(&cursor);
			}
			if (cursor<hArray.size) hArray.nodes[cursor] = i;
		}
	}
	
	//printf("size = %d\n", hArray.size);
	/*for (i=0; i<hArray.size; i++) {
		if (hArray.nodes[i]==-1) printf("-");
		else printf("%c", hArray.nodes[i]);
	}
	printf("\n");
	*/

	return hArray;
}

void destroyHuffmanTreeArray(HuffmanTreeArray htree)
{
	free(htree.nodes);
}

int decompress(char * huffman, int nbit, Coding htable[], char * buffer) 
{
	HuffmanTreeArray hArray;
	int i, n, cursor;
	hArray = makeHuffmanTreeArray(htable);
	n = 0;
	setRoot(&cursor);
	for (i=0; i<nbit; i++) {
		if (getBit(huffman, i)==0) goLeft(&cursor);
		else goRight(&cursor);
		if (cursor >= hArray.size) {
			perror("Decompress error\n");
			exit(1);
		}
		if (hArray.nodes[cursor] != -1) {
			buffer[n++] = (char) hArray.nodes[cursor];
			setRoot(&cursor);
		}
	}
	destroyHuffmanTreeArray(hArray);
	return n;
}

void decompressFile(char *input, char *output) {
	HuffmanTree htree;
	HuffmanTreeArray hArray;
	Coding htable[256] = {};
	int i, k, n=0, nbit, size, ch, cursor;
	char bits[10];
	char code[2];
	
	FILE* f1, *f2;

	char* huffman;
	
	f1 = fopen(input, "rb");
	if (f1==NULL) {
		perror("Can not open input file\n");
		exit(2);
	}
	
	fread(code, 2, 1, f1);
	if (code[0]!='H'&&code[1]!='M') {
		perror("Bad format\n");
		exit(2);
	}
	
	/* read huffman code into table */
	fread(&n, sizeof(int), 1, f1);
	printf("Read huffman table: %d chars\n", n);
	for (i=0; i<256; i++)
		htable[i].size = 0;
	for (i=0; i<n; i++)
	{
		ch = fgetc(f1);
		fread(&nbit, sizeof(int), 1, f1);
		printf("%c: %d bits\n", ch, nbit);
		htable[ch].size = nbit;
		k = nbit/8;
		if (nbit%8) k++;
		fread(bits, k, 1, f1);
		for (k=0; k<nbit; k++)
			htable[ch].bits[k] = getBit(bits, k);
	}
	hArray = makeHuffmanTreeArray(htable);
	
	f2 = fopen(output, "w+b");
	if (f2==NULL) {
		perror("Can not open output file\n");
		exit(2);
	}
	
	/* read huffman data */
	fread(&nbit, sizeof(int), 1, f1);
	size = nbit/8;
	if (nbit%8) size++;
	huffman = (char*) malloc(size);
	printf("Read huffman data: %d chars\n", size);
	fread(huffman, size, 1, f1);
	setRoot(&cursor);
	for (i=0; i<nbit; i++) {
		if (getBit(huffman, i)==0) goLeft(&cursor);
		else goRight(&cursor);
		if (cursor >= hArray.size) {
			perror("Decompress error\n");
			exit(1);
		}
		if (hArray.nodes[cursor] != -1) {
			fputc(hArray.nodes[cursor], f2);
			setRoot(&cursor);
		}
	}
	free(huffman);
	destroyHuffmanTreeArray(hArray);
	
	fclose(f1);
	fclose(f2);
	
}