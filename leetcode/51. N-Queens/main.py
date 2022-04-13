class Solution:

    def isSafe(self, i, j, board):
        for c in range(len(board)):
            for r in range(len(board)):
                if board[c][r] == 'Q' and i==c and j!=r:
                    return False
                elif board[c][r] == 'Q' and j==r and i!=c:
                    return False
                elif (i+j == c+r or i-j == c-r) and board[c][r] == 'Q':
                    return False
        return True 

    def copy_board(self, board):
        new_board = [['.' for c in range(len(board))] for r in range(len(board))]

        for r in range(len(board)):
            for c in range(len(board)):
                new_board[r][c] = board[r][c]

        return new_board

    def place_n_queens(self, n, board, r, res):
        if r == n:
            res.append(board)
            return

        for c in range(n):
            if self.isSafe(r, c, board):
                new_board = self.copy_board(board)
                new_board[r][c] = 'Q'
                self.place_n_queens(n, new_board, r+1, res)

    def solveNQueens(self, n: int) -> List[List[str]]:
        board_matrix = [['.' for _ in range(n)] for _ in range(n)]

        res = []
        self.place_n_queens(n, board_matrix, 0, res)

        res_boards = []
        for rr in res:
            res_board = ['' for _ in range(n)]
            for r in range(n):
                res_board[r] = ''.join(rr[r])
            res_boards.append(res_board)
        
        return res_boards