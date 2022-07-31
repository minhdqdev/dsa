import heapq
from collections import deque
from datetime import datetime
from typing import List

# DEFINE SOLUTION IN HERE

class Solution:
    def countNegatives(self, grid: List[List[int]]) -> int:
        # [[ 4, 3, 2,-1],
        #  [ 3, 2, 1,-1],
        #  [ 1, 1,-1,-2],
        #  [-1,-1,-2,-3]]
        
        # [[3,2],
        #  [1,0]]
        
        # [[ 3, 2],
        #  [-3,-3],
        #  [-3,-3],
        #  [-3,-3]]
        
        m, n, count = len(grid), len(grid[0]), 0
        
        # find the index of (<= -1) in the 1st column ~ mid
        left, right, mid = 0, m-1, -1
        
        while left <= right:
            mid = (right + left) // 2
            
            t = grid[mid][0]
            
            if t == -1:
                break
            elif t >= 0:
                left = mid + 1
            else:
                right = mid - 1
        
        if grid[mid][0] >= 0:
            mid += 1
        
        for r in range(0, mid):
            left, right, c = 0, n-1, -1
            
            while left <= right:
                c = (right + left) // 2
                
                t = grid[r][c]
                
                if t == -1:
                    break
                elif t >= 0:
                    left = c + 1
                else:
                    right = c - 1
                
            if grid[r][c] >= 0:
                c += 1
            
            count += (n - c)
        
        count += n * (m - mid)
        
        return count
            
            


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    grid = [
        [ 3,-1,-3,-3,-3],
        [ 2,-2,-3,-3,-3],
        [ 1,-2,-3,-3,-3],
        [ 0,-3,-3,-3,-3]
    ]

    ans = solution.countNegatives(grid)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))
