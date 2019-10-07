"""
Implement Stack using List in Python. 

This method is more efficient then implementing stack using list.
"""

from collections import deque

def printStack(s):
    for i in range(len(s)):
        print(s[i], end='\t')
    print('\n')

def main():
    s = deque()

    s.append(10)
    s.append(30)
    s.append(20)
    s.append(5)
    s.append(1)

    print("The stack is: ", end='')
    printStack(s)

    print(f"Size of stack: {len(s)}")

    print(f"Top of stack: {s[-1]}")

    s.pop()
    print("Pop stack: ")
    printStack(s)

if __name__ == "__main__":
    main()