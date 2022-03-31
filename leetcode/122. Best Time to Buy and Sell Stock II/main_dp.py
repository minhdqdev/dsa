class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # DP for stock problems
        # Time: O(N)
        # Space: O(N)
        
        # k = infinity
        # -> dp[i-1][k][0] = dp[i-1][k-1][0]
        # -> dp[i-1][k][1] = dp[i-1][k-1][1]
        
        # dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
        # dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
        #             = max(dp[i-1][k][1], dp[i-1][k][0] - prices[i])
        
        # can't build DP table as k is infinity
        # however dp[i] only depends on dp[i-1] -> can optimize to O(1) space
        
        dp_ik0, dp_ik1 = 0, -2 ** 31
        
        for i in range(len(prices)):
            dp_ik0, dp_ik1 = max(dp_ik0, dp_ik1 + prices[i]), max(dp_ik1, dp_ik0 - prices[i])
            
        
        return dp_ik0
        
        
        