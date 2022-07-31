from typing import List
from datetime import datetime

class Solution:
    def search(self, nums: List[int], target: int) -> bool:
        n = len(nums)
        shifted = 0
        
        for i in range(n-1):
            if nums[i] > nums[i+1]:
                shifted = i + 1
                break
    
        def bin_search(nums, shifted, left, right, target):
            if left > right:
                return False
        
            mid = (right + left) // 2
            real_mid = (mid + shifted) % len(nums)
            
            if nums[real_mid] == target:
                return True
            elif nums[real_mid] > target:
                return bin_search(nums, shifted, left, mid-1, target)
            else:
                return bin_search(nums, shifted, mid+1, right, target)
        
        return bin_search(nums, shifted, 0, n-1, target)


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    nums = [1,0,1,1,1]
    target = 0
    ans = solution.search(nums, target)
    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))