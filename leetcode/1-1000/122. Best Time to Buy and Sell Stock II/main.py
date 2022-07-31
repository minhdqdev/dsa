from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # Idea: need to look upfront to predict whether to sell or buy in one day.
        max_profit = 0
        n = len(prices)
        
        if n == 1:
            return 0
        
        min_price = prices[0]
        max_price = prices[0]
        
        state = 0
        
        if prices[0] >= prices[1]:
            state = 0 # wait to buy
        else:
            state = 1 # wait to sell
        
        for i in range(1, n-1):
            if state == 0: # wait to buy
                if prices[i+1] > prices[i]:
                    min_price = prices[i] # buy at min price
                    state = 1
                else:
                    pass # continue to wait
            elif state == 1: # wait to sell
                if prices[i+1] < prices[i]:
                    max_price = prices[i] # sell at max price
                    
                    max_profit += max_price - min_price
                    
                    state = 0
                else:
                    pass # continue to wait
            
        if state == 0:
            # only has one day left -> no buy
            pass
        elif state == 1:
            # the last day must has the max price -> sell
            max_profit += prices[-1] - min_price
                    
        return max_profit


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))