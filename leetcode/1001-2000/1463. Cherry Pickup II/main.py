from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def find_dp(self, grid, dp, r, c1, c2):
        if c1 < 0 or c1 >= len(grid[0]) or c2 < 0 or c2 >= len(grid[0]):
            return -1

        if dp[r][c1][c2] == -1:
            dp[r][c1][c2] = grid[r][c1] + (grid[r][c2] if c1 != c2 else 0) + max((self.find_dp(grid, dp, r+1, new_c1, new_c2) for new_c1 in (c1-1, c1, c1+1) for new_c2 in (c2-1, c2, c2+1)))

        return dp[r][c1][c2]
        
    
    def cherryPickup(self, grid: List[List[int]]) -> int:
        # memoization approach

        m, n = len(grid), len(grid[0])
        
        dp = [[[-1 for k in range(n)] for j in range(n)] for i in range(m)]

        # base cases
        for i in range(min(m, n)):
            for j in range(n-1, max(n-1-m, -1), -1):
                dp[m-1][i][j] = grid[m-1][i] + (grid[m-1][j] if i != j else 0)

        return self.find_dp(grid, dp, 0, 0, n-1)


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
    grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]

    ans = solution.cherryPickup(grid)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))