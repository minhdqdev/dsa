class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # Kadane's algorithm
        
        max_ending_here = 0
        max_profit = 0
        min_so_far = prices[0]
        
        for i in range(1, len(prices)):
            if prices[i] < min_so_far:
                min_so_far = prices[i]
                
            max_ending_here = prices[i] - min_so_far
            
            if max_ending_here > max_profit:
                max_profit = max_ending_here
            
        return max_profit