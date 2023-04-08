from collections import deque

def solution(board):
    n = len(board)

    dirs = ((0, 1), (0, -1), (1, 0), (-1, 0))
    min_dist = -1

    # 최단 거리
    visited = [[0]*n for _ in range(n)]
    q = deque([(0, 0, 1)])

    while (q):
        x, y, dist = q.popleft()
        visited[x][y] = 1

        if x == n-1 and y == n-1:
            min_dist = dist
            break

        for dx, dy in dirs:
            nx, ny = x+dx, y+dy
            if 0<=nx<n and 0<=ny<n and \
                not visited[nx][ny] and board[nx][ny] != '#':
                q.append((nx, ny, dist+1))
    if min_dist < 0:
        return [0, 0, 0]

    # 가위바위보
    max_score = -1001
    cnt = 0
    score_list = []
    visited = [[0]*n for _ in range(n)]

    q = deque([(0, 0, ' ', 1, 0)])
    while (q):
        x, y, status, dist, score = q.popleft()
        visited[x][y] = 1

        if board[x][y] == 'S' or board[x][y] == 'R' or board[x][y] == 'P':
            status = board[x][y]

        else:
            comp = board[x][y].upper()
            if comp == 'S':
                if status == 'R':
                    score += 1
                if status == 'P':
                    score -= 1
            elif comp == 'R':
                if status == 'P':
                    score += 1
                if status == 'S':
                    score -= 1
            elif comp == 'P':
                if status == 'S':
                    score += 1
                if status == 'R':
                    score -= 1

        if dist == min_dist:
            if x == n-1 and y == n-1:
                if score == max_score:
                    cnt += 1
                if score > max_score:
                    max_score = score
                    cnt = 1
            continue

        for dx, dy in dirs:
            nx, ny = x+dx, y+dy
            if 0<=nx<n and 0<=ny<n and \
                not visited[nx][ny] and board[nx][ny] != '#':
                q.append((nx, ny, status, dist+1, score))

    return [min_dist, max_score, cnt%54321]