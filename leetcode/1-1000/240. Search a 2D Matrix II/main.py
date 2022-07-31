class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        # prune matrix approach
        
        m, n = len(matrix), len(matrix[0])
        
        valid_columns = []
        valid_rows = []
        
        found = False
        
        for i in range(m):
            if matrix[i][0] <= target and matrix[i][n-1] >= target:
                valid_rows.append(i)
        
        for i in range(n):
            if matrix[0][i] <= target and matrix[m-1][i] >= target:
                valid_columns.append(i)
        
        
        for row in valid_rows:
            for col in valid_columns:
                if matrix[row][col] == target:
                    found = True
                    break
            if found:
                break
        
        return found
            