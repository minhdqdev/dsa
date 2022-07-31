from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def minDeletion(self, nums: List[int]) -> int:
        # greedy approach
        prev = -1
        res = 0
        
        for a in nums:
            if a == prev:
                res += 1
            else:
                prev = a if prev < 0 else -1
        
        return res + (prev >= 0)

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))