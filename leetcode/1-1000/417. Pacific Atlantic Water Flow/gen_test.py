from random import randint
import sys

heights = [[randint(0, 10 ** 5) for _ in range(200)] for _ in range(200)]


original_stdout = sys.stdout
with open('test.txt', 'w') as f:
    sys.stdout = f
    print(heights)
    sys.stdout = original_stdout
