#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the matrixRotation function below.
def matrixRotation(matrix, r):
    row_len = len(matrix)
    col_len = len(matrix[0])
    return

if __name__ == '__main__':
    mnr = input().rstrip().split()

    m = int(mnr[0])

    n = int(mnr[1])

    r = int(mnr[2])

    matrix = []

    for _ in range(m):
        matrix.append(list(map(int, input().rstrip().split())))

    matrixRotation(matrix, r)
