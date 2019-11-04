#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the solve function below.
def isVowel(char):
    return char in 'AEIOU'

def minion_game(string):
    # your code goes here
    stuart = 0
    kevin = 0

    sub_string_dict = {}

    for i in range(len(string)):
        for j in range(i, len(string)):
            sub_string = string[i:j+1]
            # print(f'j {j}')

            if sub_string not in sub_string_dict.keys():
                sub_string_dict[sub_string] = 0
            
                if(isVowel(string[i])):
                    kevin += string.count(sub_string)
                    # print("{} - {}".format(sub_string, string.count(sub_string)))
                else:
                    stuart += string.count(sub_string)
                    # print("{} - {}".format(sub_string, string.count(sub_string)))
        
    if stuart > kevin:
        print("Stuart " + str(stuart))
    elif stuart < kevin:
        print("Kevin " + str(kevin))
    else:
        print('Draw')
if __name__ == '__main__':
    s = input()
    minion_game(s)