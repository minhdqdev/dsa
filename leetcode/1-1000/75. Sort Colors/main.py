from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        
        Classic 2 pointers problem
        
        Use 3 pointers:
          i: <i -> 0
          j: >= i and < j -> 1
          k: >k -> 2
        """
        
        n = len(nums)
        
        if n == 1:
            return
        
        i, j, k = 0, 0, n-1
        
        while j <= k:
            if nums[j] == 0:
                nums[i], nums[j] = nums[j], nums[i]
                i += 1
                j += 1
            elif nums[j] == 1:
                j += 1
            else:
                nums[j], nums[k] = nums[k], nums[j]
                k -= 1
            
if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))