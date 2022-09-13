import heapq
from collections import deque
from datetime import datetime
from typing import List

# DEFINE SOLUTION IN HERE
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        # m x n = 3 * 10 ** 4 -> must be O(n * m)
        
       
        mark = 2
        edges = set()
        d = {}
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == '1':
                    t = 0
                    if c > 0 and grid[r][c-1] > '0':
                        grid[r][c] = grid[r][c-1]
                        t += 1
                    if r > 0 and grid[r-1][c] > '0':
                        grid[r][c] = grid[r-1][c]
                        t += 1
                    
                    if t == 2 and grid[r][c-1] != grid[r-1][c]:
                        a, b = min(grid[r][c-1], grid[r-1][c]), max(grid[r][c-1], grid[r-1][c])
                        
                        if a not in d:
                            d[a] = set([b])
                        else:
                            d[a].add(b)
                        
                        if b not in d:
                            d[b] = set([a])
                        else:
                            d[b].add(a)

                    elif t == 0:
                        grid[r][c] = str(mark)
                        mark += 1
        
        
        print(d)
        # return 0
        
        unvisited_nodes = set([_ for _ in d])
        
        count = 0
        while unvisited_nodes:
            node = unvisited_nodes.pop()

            count += 1
            
            # bfs
            q = deque([node])
            
            while q:
                a = q.popleft()
                
                for child in d[a]:
                    if child in unvisited_nodes:
                        q.append(child)
                        unvisited_nodes.remove(child)

        return count

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    grid = [["1","1","1","1","1","0","1","1","1","1"],["0","1","1","0","1","1","1","0","1","1"],["1","0","1","0","1","1","0","1","0","1"],["1","0","1","1","0","1","1","1","1","1"],["1","1","0","0","1","1","1","1","1","1"],["1","1","0","1","1","1","1","1","1","1"],["1","1","1","1","1","1","1","1","0","1"],["0","1","1","0","1","1","1","1","1","0"],["1","1","0","1","1","0","1","1","1","1"],["0","1","1","1","1","1","0","1","1","1"]]

    ans = solution.numIslands(grid)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))
