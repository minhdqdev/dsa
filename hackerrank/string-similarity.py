#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the stringSimilarity function below.
def stringSimilarity(s):
    count = 0
    temp = 0

    len_s = len(s)

    for i in range(len_s): # suffixes
        temp = 0
        for j in range(len_s - i):
            if s[j] == s[i:][j]:
                temp += 1
            else:
                break
        
        # print(temp)
        count += temp


    return count

if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    # t = int(input())

    # for t_itr in range(t):
    #     s = input()

    #     result = stringSimilarity(s)

    #     fptr.write(str(result) + '\n')

    # fptr.close()

    s = 'ababaa'

    print(stringSimilarity(s))