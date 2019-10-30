#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the matrixRotation function below.
def matrixRotation(matrix, r):
    if r == 0 or len(matrix) <= 1 or len(matrix[0]) <= 1: # don't have IndexError
        return matrix

    row_len = len(matrix)
    col_len = len(matrix[0])

    # r = r % (row_len*2 + (col_len-2)*2)

    for i in range(r):
        temp = matrix[0][0]

        # shift top
        matrix[0].pop(0)
        matrix[0].append(None)

        # shift right
        for row in range(0, row_len-1):
            matrix[row][col_len-1] = matrix[row+1][col_len-1]

        # shift bottom
        matrix[row_len-1].insert(0, None)
        matrix[row_len-1].pop()

        # shift left
        for row in range(row_len-1, 0, -1):
            matrix[row][0] = matrix[row-1][0]
        matrix[1][0] = temp

    if len(matrix) < 3 or len(matrix[0]) < 3:
        return matrix
    else:
        inner_matrix = [x[:] for x in matrix[1: row_len-1]]

        for i in range(len(inner_matrix)):
            inner_matrix[i].pop()
            inner_matrix[i].pop(0)

        inner_matrix = matrixRotation(inner_matrix, r)

        # print(inner_matrix)
        # print(matrix)
        for row in range(1, row_len-1):
            matrix[row][1:col_len-1] = inner_matrix[row-1]
        # print(matrix)
        return matrix

def print_matrix(matrix):
    for row in matrix:
        for cell in row:
            print("{} ".format(cell), end='')
        print()

if __name__ == '__main__':
    # mnr = input().rstrip().split()

    # m = int(mnr[0])

    # n = int(mnr[1])

    # r = int(mnr[2])

    # matrix = []

    # for _ in range(m):
    #     matrix.append(list(map(int, input().rstrip().split())))

    # matrixRotation(matrix, r)

    # a = [[1,2,3,4],[7,8,9,10], [13,14,15,16], [19,20,21,22], [25,26,27,28]]
    a = [[1,1], [1,1]]
    a = matrixRotation(a, 3)

    print_matrix(a)

    
