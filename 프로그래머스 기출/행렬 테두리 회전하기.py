board = []

def clockwise(x1, y1, x2, y2):
    global board
    
    hor = y2 - y1
    ver = x2 - x1
    half = hor+ver
    
    lst = [0] * (half*2)
    
    for i in range(hor):
        lst[i] = board[x1][y1+i]
        lst[half+i] = board[x2][y2-i]
    
    for j in range(ver):
        lst[hor+j] = board[x1+j][y2]
        lst[half+hor+j] = board[x2-j][y1]
    
    lst = [lst[-1]] + lst[:-1]
    for i in range(hor):
        board[x1][y1+i] = lst[i]
        board[x2][y2-i] = lst[half+i]
    
    for j in range(ver):
        board[x1+j][y2] = lst[hor+j]
        board[x2-j][y1] = lst[half+hor+j]
    
    return lst

def solution(rows, columns, queries):
    global board
    answer = []
    
    for i in range(rows):
        board.append(list(range(columns*i+1, columns*(i+1)+1)))

    for a, b, c, d in queries:
        lst = clockwise(a-1, b-1, c-1, d-1)
        answer.append(min(lst))
    
    return answer