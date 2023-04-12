from collections import deque
import copy

N = 0
dirs = ((-1, 0), (0, 1), (1, 0), (0, -1))
blocks = {}  # 최상단 좌표, 길이
blank = {}  # 최상단 좌표, 길이
cnt = 0


def bound(x, y):
    if 0 <= x < N and 0 <= y < N:
        return True
    return False


def bfs(grid, visited, i, j, fill):
    q = deque([(i, j)])

    length = 0
    while q:
        x, y = q.popleft()
        if not visited[x][y]:
            length += 1
        visited[x][y] = 1

        for dx, dy in dirs:
            nx, ny = x + dx, y + dy
            if bound(nx, ny) and grid[nx][ny] == fill and not visited[nx][ny]:
                q.append((nx, ny))

    return length


def group(grid, dic, fill, visited):
    dic.clear()

    idx = 2
    for i in range(N):
        for j in range(N):
            if grid[i][j] == fill and not visited[i][j]:
                length = bfs(grid, visited, i, j, fill)
                dic[idx] = [i, j, length]
                idx += 1


def compare(board, table, x, y, bx, by, n):
    cmp = [[0] * N for _ in range(N)]

    q = deque([(x, y, bx, by)])

    cnt = 0
    while (q):
        x, y, bx, by = q.popleft()
        if not cmp[x][y]:
            cnt += 1
        cmp[x][y] = 1

        for dx, dy in dirs:
            nx, ny = x + dx, y + dy
            b_nx, b_ny = bx + dx, by + dy
            # 다음 빈자리가 있으면
            if bound(nx, ny) and board[nx][ny] == 0 and not cmp[nx][ny]:
                # 조각도 빈자리와 모양 맞으면
                if bound(b_nx, b_ny) and table[b_nx][b_ny]:
                    q.append((nx, ny, b_nx, b_ny))
                else:
                    # 해당 모양에 안맞다면
                    return False
    if cnt == n:
        return True
    else:
        return False


def match(game_board, table):
    global cnt

    for idx, (i, j, n) in blank.items():
        for g in blocks:
            if n == blocks[g][2]:
                if compare(game_board, table, i, j, blocks[g][0], blocks[g][1], n):
                    cnt += n
                    blocks[g][2] = 0
                    blank[idx][2] = -1

                    # 매칭한 부분들 채우기
                    fill(idx, game_board, blank, 0, 1)
                    fill(g, table, blocks, 1, 0)
                    break


def fill(num, grid, dic, f, un_f):
    q = deque([(dic[num][0], dic[num][1])])

    while q:
        x, y = q.popleft()
        grid[x][y] = un_f

        for dx, dy in dirs:
            nx, ny = x + dx, y + dy
            if bound(nx, ny) and grid[nx][ny] == f:
                q.append((nx, ny))

    return grid


def rotate(table):
    # table 함수 전체 90도 시계방향
    temp = copy.deepcopy(table)

    for i in range(N):
        for j in range(N):
            table[j][N - i - 1] = temp[i][j]

    return table


def solution(game_board, table):
    global N, cnt
    N = len(game_board)

    for i in range(4):
        # 빈칸 그룹화하기
        visited = [[0] * N for _ in range(N)]
        group(game_board, blank, 0, visited)

        # 블록 그룹화하기
        visited = [[0] * N for _ in range(N)]
        group(table, blocks, 1, visited)

        # 매칭하기
        match(game_board, table)

        # 시계방향 90도
        rotate(table)

    return cnt