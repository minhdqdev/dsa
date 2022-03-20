from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def setZeroes(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        
        removing_columns = set()
        removing_rows = set()
        m, n = len(matrix), len(matrix[0])
        
        for row in range(m):
            for col in range(n):
                if matrix[row][col] == 0:
                    removing_columns.add(col)
                    removing_rows.add(row)
        
        for row in removing_rows:
            for col in range(n):
                matrix[row][col] = 0
        
        for col in removing_columns:
            for row in range(m):
                matrix[row][col] = 0
                
        


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))