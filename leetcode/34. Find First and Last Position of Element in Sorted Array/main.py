from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        # binary search -> spread to find first and last positions -> O(j-i), not good
        # binary search -> binary search -> O(log n)
        
        def binary_search(nums, left, right, target):
            if left > right:
                return -1
            
            mid = (left + right) // 2
            
            if nums[mid] == target:
                return mid
            elif target > nums[mid]:
                return binary_search(nums, mid+1, right, target)
            return binary_search(nums, left, mid-1, target)
        
        k = binary_search(nums, 0, len(nums)-1, target)
        
        if k == -1:
            return [-1, -1]
        
        def binary_search_left(nums, left, right, target):
            if left > right:
                return left
            
            mid = (left + right) // 2
            
            if target == nums[mid]:
                return binary_search_left(nums, left, mid-1, target)
            return binary_search_left(nums, mid+1, right, target)
        
        def binary_search_right(nums, left, right, target):
            if left > right:
                return right
            
            mid = (left + right) // 2
            
            if target == nums[mid]:
                return binary_search_right(nums, mid+1, right, target)
            return binary_search_right(nums, left, mid-1, target)
                
        i = binary_search_left(nums, 0, k-1, target)
        j = binary_search_right(nums, k+1, len(nums)-1, target)
        
        return [i, j]

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    nums = [2, 2]
    target = 2

    ans = solution.searchRange(nums, target)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))