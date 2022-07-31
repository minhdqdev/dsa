from typing import List

class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        # binary search row
        n = len(matrix[0])

        a = 0
        b = len(matrix) - 1
        i = 0
        
        while a < b:
            i = (a + b) // 2
            if matrix[i][0] == target:
                return True
            if matrix[i][0] > target:
                b = i - 1
            if matrix[i][0] < target:
                if matrix[i][n-1] >= target:
                    a = i
                    b = i
                else:
                    a = i + 1

        i = (a + b) // 2

        a = 0
        b = n - 1
        j = 0

        while a < b:
            j = (a + b) // 2
            if matrix[i][j] == target:
                return True
            if matrix[i][j] > target:
                b = j - 1
            else:
                a = j + 1
        

        if a == b and matrix[i][a] == target:
            return True
        
        return False
        

if __name__ == '__main__':
    matrix = [[1]]
    target = 1
    res = Solution().searchMatrix(matrix, target)
    print(res)
    
    