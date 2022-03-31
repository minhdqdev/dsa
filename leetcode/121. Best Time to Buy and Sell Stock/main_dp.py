class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # DP for stock problems
        # Time: O(N)
        # Space: O(N)
        
        # dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
        # dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i])
        #            = max(dp[i-1][1][1], -prices[i])
        
        # build DP table
        # dp[i-1][0][0] is 0 -> only need 2D array - ignore k = 1
        #
        # dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
        # dp[i][1] = max(dp[i-1][1], - prices[i])
        
        dp = [[-1, -1] for i in range(len(prices))]
        
        dp[0][0] = 0
        dp[0][1] = -prices[0]
        
        for i in range(1, len(prices)):
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
            dp[i][1] = max(dp[i-1][1], - prices[i])
        
        return dp[len(prices)-1][0]
        