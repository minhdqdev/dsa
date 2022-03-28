from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE
class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        # must be O(N) or TLE
        
        n = len(gas)

        tank = 0
        i = 0 # starting point
        j = 0
        
        while j < n:
            p = j % n
            tank += gas[p]
            
            while tank < cost[p] and i < j:
                tank = tank + cost[i] - gas[i]
                i += 1
            
            if tank < cost[p]:
                i += 1
            
            j += 1
            
            if j == n + i:
                return i
    
        return -1


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    gas = [1,2,3,4,5]
    cost = [3,4,5,1,2]
    ans = solution.canCompleteCircuit(gas, cost)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))