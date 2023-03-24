from collections import deque

N = 0
dirx = (0, -1, 0, 1)
diry = (-1, 0, 1, 0)
level = None
ladder = {}

def bfs(x, y, lv, land, height):
    global N, dirx, diry, level
    
    level[x][y] = lv
    queue = deque([[x, y]])
    
    while (queue):
        x, y = queue.popleft()
        for dx, dy in zip(dirx, diry):
            nx, ny = x+dx, y+dy
            if ((0 <= nx < N) and (0 <= ny < N)) and (level[nx][ny] == 0) and abs(land[x][y] - land[nx][ny]) <= height:
                level[nx][ny] = lv
                queue.append([nx, ny])    

def connect(x, y, land):
    global ladder, dirx, diry, level

    for dx, dy in zip(dirx, diry):
        nx, ny = x+dx, y+dy
        if ((0 <= nx < N) and (0 <= ny < N)) and (level[x][y] != level[nx][ny]):
            M = max(level[x][y], level[nx][ny])
            m = min(level[x][y], level[nx][ny])
            ladder[(m, M)] = min(ladder.get((m, M), 9999), abs(land[x][y] - land[nx][ny]))
        
def parent(graph, x):
    if graph[x] == x:
        return x
    else:
        return parent(graph, graph[x])
    
def union(graph, a, b):
    pa = parent(graph, a)
    pb = parent(graph, b)
    if pa == pb:
        return 0
    
    graph[max(pa, pb)] = min(pa, pb)
    return 1
            
def solution(land, height):
    global N, level
    
    N = len(land)
    level = [[0] * N for _ in range(N)]

    # 이동 가능한 범위 묶기
    lv = 1
    for i in range(N):
        for j in range(N):
            if not level[i][j]:
                bfs(i, j, lv, land, height)
                lv += 1
    
    # 그룹 간 연결점 찾기
    for i in range(N):
        for j in range(N):
            connect(i, j, land)
    
    # 연결점으로 최소 그래프 만들기
    sort_ladder = dict(sorted(ladder.items(), key=lambda x:x[1]))
    graph = [i for i in range(lv)]
    cost = 0
    for (a, b), val in sort_ladder.items():
        if union(graph, a, b):
            cost += val
            
    return cost