# → ↑ ← ↓ 순
d = [(1, 0), (0, 1), (-1, 0), (0, -1)]
board = []
moves = []

def dfs(x, y, itemX, itemY, dist):
    global d, board, moves
    moves[x][y] = 1
    
    for dx, dy in d:
        nx, ny = x + dx, y + dy
        if (nx, ny) == (itemX, itemY):
            return (dist + 1)/2
        
        if not moves[nx][ny] and board[nx][ny]:
            return dfs(nx, ny, itemX, itemY, dist + 1)    

def solution(rectangle, charX, charY, itemX, itemY):
    global board, moves
    # 두배 처리
    maxX = 102
    maxY = 102
    
    # 좌표는 [x좌표][y좌표] 꼴로!
    # 그림의 좌표처럼 생각했을 때는 [오른쪽 칸수][위쪽 칸수]
    board = [[0] * maxY for _ in range(maxX)]
    moves = [[0] * maxY for _ in range(maxX)]
    
    # 사각형 채우기
    for x1, y1, x2, y2 in rectangle:
        for x in range(x1 * 2, x2 * 2 + 1):
            for y in range (y1 * 2, y2 * 2 + 1):
                board[x][y] = 1
    
    # 모서리 남기고 다시 비우기
    for x1, y1, x2, y2 in rectangle:
        for x in range(x1 * 2 + 1, x2 * 2):
            for y in range (y1 * 2 + 1, y2 * 2):
                board[x][y] = 0
    
    answer = dfs(charX * 2, charY * 2, itemX * 2, itemY * 2, 0)
    
    d = [(0, -1), (-1, 0), (0, 1), (1, 0)]
    answer2 = dfs(charX * 2, charY * 2, itemX * 2, itemY * 2, 0)
    
    return min(answer, answer2)