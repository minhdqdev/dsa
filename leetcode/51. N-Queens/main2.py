
def isSafe(i, j, board):
    for c in range(len(board)):
        for r in range(len(board)):
            if board[c][r] == 'q' and i==c and j!=r:
                return False
            elif board[c][r] == 'q' and j==r and i!=c:
                return False
            elif (i+j == c+r or i-j == c-r) and board[c][r] == 'q':
                return False
    return True 

def print_board(board):
    for r in range(len(board)):
        for c in range(len(board)):
            print(board[r][c], ' ', end='')
        print()
    print()

def copy_board(board):
    new_board = [['-' for c in range(len(board))] for r in range(len(board))]

    for r in range(len(board)):
        for c in range(len(board)):
            new_board[r][c] = board[r][c]

    return new_board

def place_n_queens(n, board, r, res):
    if res:
        return
    
    if r == n:
        res.append(board)
        return
    
    for c in range(n):
        
        if isSafe(r, c, board):
            
            new_board = copy_board(board)
            new_board[r][c] = 'q'
            place_n_queens(n, new_board, r+1, res)

def placeNQueens(n, board):

    board_matrix = [['-' for _ in range(n)] for _ in range(n)]

    res = []
    place_n_queens(n, board_matrix, 0, res)

    res_boards = []
    for rr in res:
        res_board = ['' for _ in range(n)]
        for r in range(n):
            res_board[r] = ''.join(rr[r])
            
    return res_boards

if __name__ == '__main__':
    board = ['----', '----', '----', '----']
    print(placeNQueens(4, board))