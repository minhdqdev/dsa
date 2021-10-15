/*
Exercise 13/11/19

Dang Quang Minh (20176823 - minh.dq176823@sis.hust.edu.vn)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jrb.h"

void print_menu(){
    printf("1. bubblesort\n");
    printf("2. jrb\n");
    printf("0. Exit\n");
    printf("\nYour choice?: ");
}

int* read_file(const char* filename, int *size){
    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(-1);
    }

    int n;

    fscanf(fp, "%d", &n);

    *size = n;

    int *array = (int*)malloc(sizeof(int) * n);

    for(int i=0; i<n; i++){
        fscanf(fp, "%d ", array+i);
    }
    // getchar();
    fclose(fp);
    return array;
}

void write_file(const char* filename, int* array, int size){
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d\n", size);

    for(int i=0; i<size; i++){
        fprintf(fp, "%d ", *(array+i));
    }
    fprintf(fp, "\n");
    printf("WROTE TO FILE!\n\n");
    fclose(fp);
}

void printArray(int *a, int size){
    for(int i=0; i<size; i++){
        printf("%d ", *(a+i));
    }
    printf("\n\n");
}

void bubbleSort(int *array, int size){
    // int temp;
    for(int i=0; i<size-1; i++){
        for(int k=0; k<size-1-i; k++){
            if(array[k] > array[k+1]){
                //swap
                int temp = array[k];
                array[k] = array[k+1];
                array[k+1] = temp;
            }
        }
    }
}

int main(){
    int ans;
    int running = 1;

    while(running){
        print_menu();
        scanf("%d", &ans); getchar();

        switch(ans){
            case 1:{
                printf("1.a)\n");
                int size;
                int* array = read_file("in.txt", &size);
                printArray(array, size);

                printf("1.b)\n");
                array = read_file("in.txt", &size);
                bubbleSort(array, size);
                printArray(array, size);

                printf("1.c)\n");
                write_file("out_bubblesort.txt", array, size);
                free(array);
                break;
            }
            case 2:{
                // Load jrb
                printf("2.a)\n");
                JRB tree = make_jrb();
                int size;
                int *array = read_file("in.txt", &size);

                for(int i=0; i<size; i++){
                    JRB node = jrb_find_int(tree, array[i]);
                    if(node == NULL){
                        JRB newTree = make_jrb();
                        node = jrb_insert_int(tree, array[i], new_jval_v(newTree));
                    }
                    JRB subtree = (JRB)jval_v(node->val);
                    int i = 0;
                    JRB travNode;
                    jrb_traverse(travNode, subtree) i++;
                    jrb_insert_int(subtree, i+1, new_jval_i(1));
                }

                // Traverse to print
                JRB node;
                jrb_traverse(node, tree){
                    JRB subtree = (JRB)jval_v(node->val);
                    JRB travNode;
                    jrb_traverse(travNode, subtree) printf("%d ", jval_i(node->key));
                }
                printf("\n\n");

                printf("2.b)\n");
                // Traverse to write to file
                FILE *fp = fopen("out_rbt.txt", "w");
                fprintf(fp, "%d\n", size);
                jrb_traverse(node, tree){
                    JRB subtree = (JRB)jval_v(node->val);
                    JRB travNode;
                    jrb_traverse(travNode, subtree) fprintf(fp,"%d ", jval_i(node->key));
                }
                fprintf(fp, "\n");
                fclose(fp);
                printf("WROTE TO FILE!\n\n");

                // free
                jrb_traverse(node, tree){
                    JRB subtree = (JRB)jval_v(node->val);
                    jrb_free_tree(subtree);
                }
                jrb_free_tree(tree);
                free(array);

                break;
            }
            case 0:{
                running = 0;
                break;
            }
            default: break;
        }
    }
    return 0;
}