from typing import List

class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        if len(nums) < 3:
            return []
        
        nums.sort()
        
        z = -1
        for i in range(len(nums)-1, -1, -1):
            if nums[i] <= 0:
                z = i
                break
        if z == -1:
            return []
        
        res = []
        
        # Case: right side has 0 items -> left side has 3 items -> must be [0,0,0]
        if z >= 2 and nums[z] == 0 and nums[z-1] == 0 and nums[z-2] == 0:
            res.append([0, 0, 0])
        
        # Case: right side has 1 items -> left side has 2 items
        if z >= 1:
            prev = -1
            i = z + 1
            while i < len(nums):
                if nums[i] == prev:
                    i += 1
                    continue

                target = 0 - nums[i]
                prev = nums[i]

                a = 0
                b = z
                while a < b:
                    s = nums[a] + nums[b]

                    if s == target:
                        res.append([nums[a], nums[b], nums[i]])

                        while a < b:
                            if nums[a+1] != nums[a]:
                                a += 1
                                break
                            else:
                                a += 1
                    elif s > target:
                        b -= 1
                    else:
                        a += 1
                i += 1
        
        # Case: left side has 1 items -> right side has 2 items
        if z < len(nums)-2:
            prev = 1
            i = 0
            while i <= z:
                if nums[i] == prev:
                    i += 1
                    continue

                target = 0 - nums[i]
                prev = nums[i]

                a = z+1
                b = len(nums)-1
                while a < b:
                    s = nums[a] + nums[b]

                    if s == target:
                        res.append([nums[i], nums[a], nums[b]])

                        while a < b:
                            if nums[a+1] != nums[a]:
                                a += 1
                                break
                            else:
                                a += 1
                    elif s > target:
                        b -= 1
                    else:
                        a += 1
                i += 1
        
        return res

    
if __name__ == '__main__':
    nums = [-2,0,1,1,2]
    res = Solution().threeSum(nums)

    print(res)