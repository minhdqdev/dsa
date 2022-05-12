from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE
class Solution:
    def minDeletion(self, A):
        res, pre = 0, -1
        for a in A:
            if a == pre:
                res += 1
            else:
                old_pre = pre
                pre = a if pre < 0 else -1

                print(old_pre, pre, a)
        return res + (pre >= 0)

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    nums = [1,1,2,2,3,3]
    ans = solution.minDeletion(nums)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))