from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def matrixReshape(self, mat: List[List[int]], r: int, c: int) -> List[List[int]]:

        m, n = len(mat), len(mat[0])
        
        if (m == r and n == c) or (m * n != r * c):
            return mat
    
        res = []
        
        for row in range(m):
            for col in range(n):
                i = n * row + col
                
                if i % c == 0:
                    res.append([])
                
                res[-1].append(mat[row][col])
        
        
        return res


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))