class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        # O(log n) -> must be binary search
        
        def binary_search(nums, left, right):
            mid = (left + right) // 2
            
            if nums[mid] > nums[mid-1] and nums[mid] > nums[mid+1]: # peak
                return mid
            elif nums[mid] > nums[mid-1]: # peak must be in the right
                return binary_search(nums, mid+1, right)
            return binary_search(nums, left, mid-1)
    
        if len(nums) == 1 or nums[0] > nums[1]:
            return 0
        
        if nums[-1] > nums[-2]:
            return len(nums)-1
        
        return binary_search(nums, 1, len(nums)-2)
