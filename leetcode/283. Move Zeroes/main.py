class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        i, j = 0, 0
        
        for i in range(len(nums)):
            if nums[i] != 0:
                if i != j:
                    nums[j] = nums[i]
                    nums[i] = 0
                j += 1
            
        return nums
        