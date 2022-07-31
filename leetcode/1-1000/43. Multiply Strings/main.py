from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE
class Solution:
    def multiply(self, num1: str, num2: str) -> str:
        m, n = len(num1), len(num2)
        s = [0] * (m + n)
        h = len(s)
        
        for j in range(n-1, -1, -1): # iterate the 2nd number
            if num2[j] == "0": # ignore multiplying with 0
                continue
                
            rem = 0
            for i in range(m-1, -1, -1): # iterate the 1st number
                ri = h-m-n+i+j+1
                a = int(num1[i]) * int(num2[j]) + rem + s[ri]
                
                rem = a // 10 if a > 9 else 0
                s[ri] = a % 10
            
            if rem > 0:
                ri = h-m-n+j
                a = rem + s[ri]
                
                rem = a // 10 if a > 9 else 0
                
                s[ri] = a % 10
                if rem:
                    s[ri-1] = rem

        # finalize the result
        k = 0
        while k < h:
            if s[k]:
                break
            k += 1
        
        if k == h:
            return "0"
        
        return ''.join(str(x) for x in s[k:])

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()

    # RUN MAIN FUNCTION IN HERE
    num1 = "123"
    num2 = "9"

    ans = solution.multiply(num1, num2)

    end = datetime.now()

    print(ans)
    print("1107", "1107" == ans)
    print('\nRuntime:', (end-start))