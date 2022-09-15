def solution(maps):
    direction = [(0, 1), (1, 0), (-1, 0), (0, -1)]
    n = len(maps)
    m = len(maps[0])
    
    visit = [[0 for _ in range(m)] for _ in range(n)]
    queue = []

    queue.append((n-1, m-1, 1))

    while queue:
        x, y, cnt = queue.pop(0)
        
        if (x, y) == (0, 0):
            return cnt

        if x in [-1, n] or y in [-1, m] or visit[x][y]==1 or maps[x][y]==0:
            continue

        visit[x][y] = 1
        for dx, dy in direction:
            queue.append((x+dx, y+dy, cnt+1))

    return -1