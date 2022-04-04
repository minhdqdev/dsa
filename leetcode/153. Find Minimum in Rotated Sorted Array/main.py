class Solution:
    def findMin(self, nums: List[int]) -> int:
        # need to find the position i that is valley.
        
        def binary_search(nums, left, right):
            mid = (left + right) // 2

            if nums[mid] < nums[mid-1] and nums[mid] < nums[mid+1]:
                return mid # valley
            elif nums[mid] > nums[mid-1] and nums[mid] > nums[mid+1]:
                return mid+1
            
            if left < mid-1:
                if nums[left] > nums[mid-1]: # contain valley
                    return binary_search(nums, left, mid-1)
                return binary_search(nums, mid+1, right)
            elif mid+1 < right:
                if nums[mid+1] > nums[right]:
                    return binary_search(nums, mid+1, right)
                return binary_search(nums, left, mid-1)
            
            return min(nums[left], nums[right])

        if len(nums) == 1:
            return nums[0]
        elif len(nums) == 2:
            return min(nums[0], nums[1])
        elif nums[0] < nums[1] and nums[0] < nums[-1]:
            return nums[0]
        elif nums[-1] < nums[-2] and nums[-1] < nums[0]:
            return nums[-1]
        elif nums[0] > nums[1] and nums[0] > nums[-1]:
            return nums[1]
        elif nums[-1] > nums[-2] and nums[-1] > nums[0]:
            return nums[0]
        
        # up to this point, nums[0] and nums[-1] can't be valley or peak.
        
        return nums[binary_search(nums, 1, len(nums)-2)]