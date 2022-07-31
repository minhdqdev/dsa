class Solution:
    def search(self, nums: List[int], target: int) -> int:
        # find k
        n = len(nums)
        
        if n == 1:
            return 0 if target == nums[0] else -1
        
        k = 0
        for i in range(1, n):
            if nums[i] < nums[i-1]:
                k = n - i
        
        # binary search
        def bin_search(nums, k, left, right, target):
            if left > right:
                return -1
            
            mid = (right + left) // 2
            rmid = (n + mid - k) % n
            
            if nums[rmid] == target:
                return rmid
            elif nums[rmid] > target:
                return bin_search(nums, k, left, mid-1, target)
            else:
                return bin_search(nums, k, mid+1, right, target)
        
        return bin_search(nums, k, 0, n-1, target)
