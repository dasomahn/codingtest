def solution(col, row, puddles):
    board = [[1] * col for _ in range(row)]
    
    for x, y in puddles:
        board[y-1][x-1] = 0
    
    for r in range(row):
        for c in range(col):
            if not r and not c:
                continue
            if board[r][c]:
                if r == 0:
                    board[0][c] = board[0][c-1]
                elif c == 0:
                    board[r][0] = board[r-1][0]
                else:
                    board[r][c] = board[r][c-1] + board[r-1][c]
    
    return board[row-1][col-1] % 1000000007