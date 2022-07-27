import heapq
from collections import deque
from datetime import datetime
from typing import List

# DEFINE SOLUTION IN HERE
class Solution:
    def count_ones(self, row):
        left, right, mid = 0, len(row)-1, -1
        
        while left <= right:
            mid = (right + left) // 2
            t = row[mid]
            
            if t == 0:
                right = mid - 1
            elif t == 1:
                left = mid + 1
        
        while mid < len(row) and row[mid] == 1:
            mid += 1

        return mid
        
    
    def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:
        a = []
        
        for i, row in enumerate(mat):
            a.append((i, self.count_ones(row)))
        
        print(a)

        def cmp(a, b):
            if a[1] < b[1]:
                return -1
            elif a[1] > b[1]:
                return 1
            else:
                res = a[0] < b[0]
                
                if res:
                    return -1
                return 1
        
        # sort
        for i in range(len(a) - 1, 0, -1):
            for j in range(0, i):
                if cmp(a[j], a[j+1]) == 1:
                    # swap
                    a[j], a[j+1] = a[j+1], a[j]

        return [_[0] for _ in a[:k]]
        
        


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    mat = [[1,1,0,0,0],[1,1,1,1,0],[1,0,0,0,0],[1,1,0,0,0],[1,1,1,1,1]]
    k = 3

    ans = solution.kWeakestRows(mat, k)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))
