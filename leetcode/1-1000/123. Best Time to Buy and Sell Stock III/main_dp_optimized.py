from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # DP for stock problems
        # Time: O(N)
        # Space: O(1)
        
        # k = 2
        
        # T[i][2][0] = max(T[i-1][2][0], T[i-1][2][1] + prices[i])
        # T[i][2][1] = max(T[i-1][2][1], T[i-1][1][0] - prices[i])
        # T[i][1][0] = max(T[i-1][1][0], T[i-1][1][1] + prices[i])
        # T[i][1][1] = max(T[i-1][1][1], -prices[i])
        
        # build dp table
        dp_i20, dp_i21, dp_i10, dp_i11 = 0, -2 ** 31, 0, -2 ** 31
        
        for i in range(len(prices)):
            dp_i20 = max(dp_i20, dp_i21 + prices[i])
            dp_i21 = max(dp_i21, dp_i10 - prices[i])
            dp_i10 = max(dp_i10, dp_i11 + prices[i])
            dp_i11 = max(dp_i11, - prices[i])
        
        return dp_i20


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))