class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # DP for stock problems
        # Time: O(N)
        # Space: O(1) - optimized
        
        dp_i10, dp_i11 = 0, - 2 ** 31
        
        for i in range(len(prices)):
            dp_i10 = max(dp_i10, dp_i11 + prices[i])
            dp_i11 = max(dp_i11, - prices[i])
        
        return dp_i10
        