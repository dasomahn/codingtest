from collections import deque
import copy

N = 0
dirs = ((-1, 0), (0, 1), (1, 0), (0, -1))
blocks = {}  # 최상단 좌표, 길이
blanks = {}  # 최상단 좌표, 길이
cnt = 0


def bound(x, y):
    if 0 <= x < N and 0 <= y < N:
        return True
    return False


def bfs(grid, visited, i, j, fill):
    q = deque([(i, j)])

    points = []
    minx, miny = 50, 50

    while q:
        x, y = q.popleft()
        minx = min(minx, x)
        miny = min(miny, y)

        if not visited[x][y]:
            points.append((x, y))
        visited[x][y] = 1

        for dx, dy in dirs:
            nx, ny = x + dx, y + dy
            if bound(nx, ny) and grid[nx][ny] == fill and not visited[nx][ny]:
                q.append((nx, ny))

    return points, minx, miny


def group(grid, dic, fill, visited):
    dic.clear()

    for i in range(N):
        for j in range(N):
            if grid[i][j] == fill and not visited[i][j]:
                points, minx, miny = bfs(grid, visited, i, j, fill)
                dic[(minx, miny)] = sorted(points)


def compare(blank_pos, block_pos):
    a_list = blanks[blank_pos]
    o_list = blocks[block_pos]

    a_minx, a_miny = blank_pos
    o_minx, o_miny = block_pos

    for (a_x, a_y), (o_x, o_y) in zip(a_list, o_list):
        # 상대좌표 비교
        if (a_x - a_minx == o_x - o_minx) and (a_y - a_miny == o_y - o_miny):
            continue
        else:
            return False
    return True


def match(game_board, table):
    global cnt

    for blank in blanks:
        for block in blocks:
            if blanks[blank] and blocks[block] and len(blanks[blank]) == len(blocks[block]):
                if compare(blank, block):
                    cnt += len(blanks[blank])
                    blocks[block].clear()
                    blanks[blank].clear()

                    # 매칭한 부분들 채우기
                    fill(game_board, blanks[blank], 1)
                    fill(table, blocks[block], 0)
                    break


def fill(grid, lst, fill):
    for x, y in lst:
        grid[x][y] = fill


def rotate():
    # block 그룹한거 내용 전부 90도 회전
    temp = copy.deepcopy(blocks)
    blocks.clear()

    for (minx, miny) in temp:
        lst = temp[(minx, miny)]
        if not lst:
            continue
        newlst = []

        # 회전된거 기준으로 최소x, 최소y 다시 업데이트
        minx, miny = 50, 50
        for (x, y) in lst:
            nx, ny = y, N - x - 1
            newlst.append((nx, ny))
            minx = min(minx, nx)
            miny = min(miny, ny)

        blocks[minx, miny] = sorted(newlst)


def solution(game_board, table):
    global N, cnt
    N = len(game_board)

    # 빈칸 그룹화하기
    visited = [[0] * N for _ in range(N)]
    group(game_board, blanks, 0, visited)

    # 블록 그룹화하기
    visited = [[0] * N for _ in range(N)]
    group(table, blocks, 1, visited)

    match(game_board, table)
    for i in range(3):
        if len(blocks) == 0:
            break

        # 시계방향 90도
        rotate()

        # 매칭하기
        match(game_board, table)

    return cnt