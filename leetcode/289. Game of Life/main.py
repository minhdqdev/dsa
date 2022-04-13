from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def gameOfLife(self, board: List[List[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        m, n = len(board), len(board[0])
        
        def count_live_neighbors(board, row, col):
            m, n = len(board), len(board[0])
            count = sum((board[y][x] for y in range(max(row-1, 0), min(row+2, m)) for x in range(max(col-1, 0), min(col+2, n))))
            return count if board[row][col] == 0 else (count - 1)
        
        new_state = [[0 for x in range(n)] for y in range(m)]

        for y in range(m):
            for x in range(n):
                c = count_live_neighbors(board, y, x)
                if board[y][x] == 0:
                    if c == 3:
                        new_state[y][x] = 1
                else:
                    if c < 2 or c > 3:
                        new_state[y][x] = 0
                    else:
                        new_state[y][x] = 1

        # update board
        for y in range(m):
            for x in range(n):
                board[y][x] = new_state[y][x]

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
    ans = solution.gameOfLife(board)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))