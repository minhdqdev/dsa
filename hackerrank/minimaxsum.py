#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the miniMaxSum function below.
def miniMaxSum(arr):
    print("{} {}".format(sum(sorted(arr)[:len(arr)-1]), sum(sorted(arr)[1:])))

if __name__ == '__main__':
    arr = list(map(int, input().rstrip().split()))

    miniMaxSum(arr)
