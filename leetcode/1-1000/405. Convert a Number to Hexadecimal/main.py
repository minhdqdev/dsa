from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def toHex(self, num: int) -> str:
        x = [str(_) for _ in range(10)] + ['a', 'b', 'c', 'd', 'e', 'f']
        h = ['0' for i in range(8)]
        
        if num < 0:
            num = 16 ** 8 - abs(num)
        
        for i in range(8):
            v = num // (16 ** (7-i))
            h[i] = x[v]
            num %= (16 ** (7-i))

        non_zero_index = 0
        for i in range(8):
            if h[i] != '0':
                non_zero_index = i
                break
        
        return ''.join(h[non_zero_index:])      

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.toHex(-1)

    print(ans)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))