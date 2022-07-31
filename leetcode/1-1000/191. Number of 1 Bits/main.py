from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def hammingWeight(self, n: int) -> int:
        count = 0
        
        if n < 0:
            n = -n
            count += 1
            
        while n > 0:
            if n % 2 != 0:
                count += 1
            n >>= 1
        
        return count

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))