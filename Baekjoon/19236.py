import copy


def outbound(x, y):
    if (0 <= x < 4) and (0 <= y < 4):
        return False
    return True


def find_fish(num, graph):
    for i in range(4):
        for j in range(4):
            if graph[i][j][0] == num:
                return (i, j)

    return (-1, -1)


def fish_move(graph):
    for i in range(1, 17):
        # 물고기 번호 i의 위치 갖고오기
        x, y = find_fish(i, graph)

        if x == -1 and y == -1:  # 먹힌 물고기
            continue

        # 물고기 번호 i의 방향 갖고오기
        dx, dy = dirs[graph[x][y][1]]
        nx, ny = x + dx, y + dy

        # 범위 나갔거나 상어가 있는 위치(-1)라면
        cnt = 0
        while (outbound(nx, ny) or graph[nx][ny][0] == -1) and cnt < 8:
            # 반시계 회전
            graph[x][y][1] = graph[x][y][1] % 8 + 1
            dx, dy = dirs[graph[x][y][1]]
            nx, ny = x + dx, y + dy

            # 물고기가 못움직이는 경우 체크를 위해
            cnt += 1

        if cnt == 8:
            continue

        graph[x][y], graph[nx][ny] = graph[nx][ny], graph[x][y]


def shark_can_move(x, y, ndir, graph):
    mov = []
    for i in range(1, 4):  # 1, 2, 3
        nx = x + ndir[0] * i
        ny = y + ndir[1] * i
        if not outbound(nx, ny) and graph[nx][ny][0] > 0:
            # 공간 경계 넘지 않고 물고기가 있는 칸
            mov.append((nx, ny))

    return mov


def dfs(x, y, total, graph):
    global M

    n, dirnum = graph[x][y]
    graph[x][y][0] = -1 # 현재 상어 위치 표시
    total += n

    fish_move(graph)

    movable = shark_can_move(x, y, dirs[dirnum], graph)
    if not movable:
        M = max(M, total)
        return

    graph[x][y][0] = 0 # 상어 이동, 빈자리
    for nx, ny in movable:
        # 백트래킹을 위해 deepcopy 넘기기
        dfs(nx, ny, total, copy.deepcopy(graph))


dirs = {1: (-1, 0), 2: (-1, -1), 3: (0, -1), 4: (1, -1),
        5: (1, 0), 6: (1, 1), 7: (0, 1), 8: (-1, 1)}

# init
M = -1
grid = [[], [], [], []]  # [숫자, 방향] 꼴
for x in range(4):
    line = list(map(int, input().split()))
    for y in range(4):
        grid[x].append([line[2 * y], line[2 * y + 1]])

# solve
dfs(0, 0, 0, grid)
print(M)
