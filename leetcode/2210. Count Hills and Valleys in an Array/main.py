from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def countHillValley(self, nums: List[int]) -> int:
        count = 0
        state = 0
        for i in range(1, len(nums)):
            if state == 0:
                if nums[i] > nums[i-1]:
                    state = 1 # can be hill
                elif nums[i] < nums[i-1]:
                    state = 2 # can be valley
                else:
                    continue
            elif state == 1:
                if nums[i] < nums[i-1]: # end of hill
                    count += 1
                    state = 2 # can be valley
                elif nums[i] > nums[i-1]: # still going up the hill
                    continue
                else: # still the part of the hill
                    continue
            elif state == 2:
                if nums[i] > nums[i-1]: # end of valley
                    count += 1
                    state = 1 # can be hill
                elif nums[i] < nums[i-1]: # still going down the valley
                    continue
                else: # still the part of the valley
                    continue

        return count


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    nums = [2,4,1,1,6,5]
    nums = [6,6,5,5,4,1]

    ans = solution.countHillValley(nums)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))