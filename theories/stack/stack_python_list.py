"""
Implement Stack using List in Python.

Implement stack with list will encounter speed issues. 
List is designed for fast accessing. So a[1] is really quick.
But append() can be slow when stack is getting larger. The list has to allocate new memories.

-> Consider implement stack using deque for fast popping and appending.
"""

def printStack(s):
    for i in range(len(s)):
        print(s[i], end='\t')
    print('\n')

def main():
    s = []

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