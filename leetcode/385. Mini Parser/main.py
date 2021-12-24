# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
from collections import deque

class NestedInteger:
   def __init__(self, value=None):
       """
       If value is not specified, initializes an empty list.
       Otherwise initializes a single integer equal to value.
       """

   def isInteger(self):
       """
       @return True if this NestedInteger holds a single integer, rather than a nested list.
       :rtype bool
       """

   def add(self, elem):
       """
       Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
       :rtype void
       """

   def setInteger(self, value):
       """
       Set this NestedInteger to hold a single integer equal to value.
       :rtype void
       """

   def getInteger(self):
       """
       @return the single integer that this NestedInteger holds, if it holds a single integer
       Return None if this NestedInteger holds a nested list
       :rtype int
       """

   def getList(self):
       """
       @return the nested list that this NestedInteger holds, if it holds a nested list
       Return None if this NestedInteger holds a single integer
       :rtype List[NestedInteger]
       """

class Solution:
    def deserialize(self, s: str) -> NestedInteger:
        res = NestedInteger()
        
        state = 0;    
        ss = deque()
        
        numbers = [str(i) for i in range(10)]
        numbers.append('-')
        temp = ''
        
        for c in s:
            if state == 0: # begin
                if c == '[':
                    ss.append(NestedInteger())
                    temp = ''
                    state = 1
                elif c in numbers: # must be a single number
                    return NestedInteger(int(s))
            elif state == 1: # in list, wait for number or [ or ]
                if c in numbers:
                    temp += c
                    state = 2
                elif c == '[':
                    ss.append(NestedInteger())
                    state = 1
                elif c == ']':
                    if len(ss) >= 2:
                        ss[-2].add(ss[-1])
                        ss.pop()
                    else:
                        return ss[0]
            elif state == 2: # in list, wait for , or ] to parse number
                if c in numbers:
                    temp += c
                elif c == ',':
                    if temp:
                        ss[-1].add(NestedInteger(int(temp)))
                        temp = ''
                    state = 1
                elif c == ']':
                    if temp:
                        ss[-1].add(NestedInteger(int(temp)))
                        temp = ''
                    if len(ss) >= 2:
                        ss[-2].add(ss[-1])
                        ss.pop()
                    else:
                        return ss[0]
                

    
    

    
    
    
    
    
    
        