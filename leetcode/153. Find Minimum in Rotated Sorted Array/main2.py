from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE
class Solution:
    def __init__(self):
        self.min_val = 0
    
    def binary_search(self, nums, left, right):
        if left > right:
            return

        mid = (left + right) // 2

        if nums[mid] < nums[mid-1] and nums[mid] < nums[mid+1]:
            self.min_val = nums[mid]
            return
        
        self.binary_search(nums, left, mid-1)
        self.binary_search(nums, mid+1, right)
        
    def findMin(self, nums: List[int]) -> int:
        # need to find the position i that is valley.
        
        if len(nums) == 1:
            return nums[0]
        elif len(nums) == 2:
            return min(nums[0], nums[1])
        elif nums[0] < nums[1] and nums[0] < nums[-1]:
            return nums[0]
        elif nums[-1] < nums[-2] and nums[-1] < nums[0]:
            return nums[-1]
        
        self.binary_search(nums, 1, len(nums)-2)
        return self.min_val


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    [3,4,5,1,2]
    [4,5,6,7,0,1,2]
    [11,13,15,17]
    [7,8,1,2,3,4,5,6]
    [2,3,1]
    [4,5,1,2,3]
    [4,5,6,1,2,3]

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))