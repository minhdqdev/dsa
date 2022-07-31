from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        d = {}
        
        threshold = len(nums) // 2
        
        for n in nums:
            if n not in d:
                d[n] = 1
            else:
                d[n] += 1
            
            if d[n] > threshold:
                return n


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))