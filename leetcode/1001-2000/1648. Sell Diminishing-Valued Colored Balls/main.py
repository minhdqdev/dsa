from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

from queue import PriorityQueue

class Solution:
    def maxProfit(self, inventory: List[int], orders: int) -> int:
        # at one point, sell the ball with the highest stock
        
        q = PriorityQueue()
        
        min_priority = 10 ** 9
        
        for item in inventory:
            q.put((min_priority - item, item))
        
        total = 0
        
        while orders:
            priority, item = q.get()
            
            if not q.empty():
                next_priority, next_item = q.get()
                q.put((next_priority, next_item))
                
                n = min(orders, item - next_item + 1) # incoming order
                orders -= n
                total += n * (2 * item - n + 1) // 2

                print(item-n, next_item)
                q.put((priority + n, item-n))
            else:
                n = min(orders, item) # incoming order
                orders -= n
                total += n * (2 * item - n + 1) // 2
                q.put((priority + n, item-n))

        return total % (10**9 + 7)

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    # inventory = [3,5]
    # orders = 6
    inventory = [76]
    orders = 22

    inventory = [497978859,167261111,483575207,591815159]
    orders = 836556809

    ans = solution.maxProfit(inventory, orders)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))