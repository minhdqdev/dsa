from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def findAns(self, n, nums, lookup):
        if lookup[n] is not None:
            return lookup[n]
        
        for i in range(n-1, -1, -1):
            if nums[i] >= n - i and self.findAns(i, nums, lookup):
                lookup[n] = True
                return lookup[n]
        lookup[n] = False
        return lookup[n]
        
    
    def canJump(self, nums: List[int]) -> bool:
        if len(nums) == 1:
            return True
        elif len(nums) == 2:
            return nums[0] >= 1
        
        # top down method
        lookup = [None for i in range(len(nums))]
        lookup[0] = True
        lookup[1] = nums[0] >= 1
        
        return self.findAns(len(nums)-1, nums, lookup)
            


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE
    nums = [3,2,1,0,4]

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.canJump(nums)

    end = datetime.now()

    print(ans, (end-start))