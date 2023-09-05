def bound(x, y):
    if (0 <= x < r) and (0 <= y < c):
        if (x, y) not in [(up, 0), (down, 0)]:
            return True
    return False


def ans_diffusion():  # 1초마다 미세먼지가 퍼지는 동작
    change = [[0] * c for _ in range(r)]
    for x in range(r):
        for y in range(c):
            if grid[x][y] > 0:  # 미세먼지가 있는 경우
                tmp = 0
                for i in range(4):  # 4방면으로 퍼짐
                    ax = x + dirs[i][0]
                    ay = y + dirs[i][1]

                    if bound(ax, ay):
                        change[ax][ay] += grid[x][y] // 5
                        tmp += grid[x][y] // 5
                grid[x][y] -= tmp

    for x in range(r):
        for y in range(c):
            grid[x][y] += change[x][y]


def diffusion():
    dust = [[0] * c for _ in range(r)]

    for x in range(r):
        for y in range(c):
            div = grid[x][y] // 5
            if div > 0:
                for dx, dy in dirs:
                    nx, ny = x + dx, y + dy
                    if (0 <= nx < r) and (0 <= ny < c):
                        if grid[nx][ny] != -1:
                            dust[nx][ny] += div
                            grid[x][y] -= div

    for x in range(r):
        for y in range(c):
            grid[x][y] += dust[x][y]


def clean(direction, x, y):
    if x == up:
        edge = 0
    elif x == down:
        edge = r - 1
    edges = [(x, 0), (x, c - 1), (edge, 0), (edge, c - 1)]

    for dx, dy in direction:
        while True:
            nx, ny = x + dx, y + dy
            grid[x][y] = grid[nx][ny]
            x, y = nx, ny

            if (nx, ny) in edges:
                break


r, c, t = map(int, input().split())
grid = [list(map(int, input().split())) for _ in range(r)]

for i in range(r):
    if grid[i][0] == -1:
        up, down = i, i + 1
        break

dirs = ((-1, 0), (0, 1), (1, 0), (0, -1))
c_dirs = ((1, 0), (0, 1), (-1, 0), (0, -1))

for _ in range(t):
    diffusion()

    clean(dirs, up, 0)
    clean(c_dirs, down, 0)

    grid[up][0] = -1
    grid[up][1] = 0
    grid[down][0] = -1
    grid[down][1] = 0

total = sum(sum(grid[r]) for r in range(r))
print(total+2)
