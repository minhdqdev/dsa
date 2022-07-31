from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

# class Solution:
#     def singleNumber(self, nums: List[int]) -> int:
#         return sum(set(nums))*2 - sum(nums)


# optimal solution
# xor operation between two same number is 0
# xor of 0 and a number is the number itself.
class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        xor = 0
        for num in nums:
            xor ^= num
        
        return xor
        


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))