n = 1
dirs = ((0, 1), (0, -1), (1, 0), (-1, 0))

def find(garden, day, sx, sy):
    for x in range(sx, n):
        for y in range(n):
            if x<= sx and y <= sy:
                continue
            
            if garden[x][y] == day:
                for dx, dy in dirs:
                    nx, ny = x+dx, y+dy
                    if 0<=nx<n and 0<=ny<n and not garden[nx][ny]:
                        garden[nx][ny] = day+1
                return (x, y)

    return (-1, -1)

def solution(garden):
    global n
    n = len(garden)
    
    day = 0
    while any(0 in gar for gar in garden):
        day += 1

        sx, sy = find(garden, day, 0, 0)
        while ((sx, sy) != (-1, -1)):
            sx, sy = find(garden, day, sx, sy)

    return day
