#!/bin/python3

import os
import sys

#
# Complete the countStrings function below.
#

def countCases(arr, remind, l):
    """
    Input:
        arr[]: contain the lengths of elements
        remind[]: containt the result of countCases with l is the index of remind[].
        l: length of required strings
    Output:
        count: the number of way to construct a string with length l using elements from arr.
    Example:
        arr = [1,1]
        l = 5
        -> count = 32
    """
    if l == 0:
        return 0

    temp_count = len(list(filter(lambda x: x == l, arr)))

    temp_count_2 = 0
    for k in range(1, l):
        if remind[k] is not None:
            if remind[l-k] is not None:
                temp_count_2 += remind[k] + remind[l-k]
            else:
                temp_count_2 += remind[k] + countCases(arr, remind, l-k)
        else:
            if remind[l-k] is not None:
                temp_count_2 += countCases(arr, remind, k) + remind[l-k]
            else:
                temp_count_2 += countCases(arr, remind, k) + countCases(arr, remind, l-k)

    remind[l] = temp_count_2 + temp_count
    return temp_count_2 + temp_count


def countStrings(r, l):
    count = 0
    stack = []

    s1 = []
    s2 = []

    has_brace = 0

    for i, c in enumerate(r):
        stack.append(c)

        if c == '(':
            has_brace +=1
        elif c == ')':
            has_brace -= 1
            last_brace_index = r.rfind('(')

            expression = r[last_brace_index+1: i]
            print(expression)

            if '|' in expression:
                if s1 is None: # ex: a|b
                    line_index = expression.find('|')
                    s1 = [len(expression)-1]
                else:
                    if s2 is None:
                        continue
                    else:
                        temp = []
                        for i in range(len(s1)):
                            for j in range(len(s2)):
                                temp.append(s1[i] + s2[j])
                        s1 = temp[:]
            if '*' in expression:
                if s1 is None:
                    s1 = [l]
                else:
                    return # TODO



    return count

if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    # t = int(input())

    # for t_itr in range(t):
    #     rl = input().split()

    #     r = rl[0]

    #     l = int(rl[1])

    #     result = countStrings(r, l)

    #     fptr.write(str(result) + '\n')

    # fptr.close()

    # r = "((ab)|(ba))"
    # l = 2

    # result = countStrings(r, l)
    # print("Result: {}".format(result))

    l = 5
    arr = [1,1]
    remind = [None for x in range(l+1)]
    remind[0] = 0
    remind[1] = len(list(filter(lambda x: x == 1, arr)))

    print("CountCases: {}".format(countCases(arr, remind, l)))

    print(remind)
