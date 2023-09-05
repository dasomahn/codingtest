import sys

sys.stdin = open("19237input.txt", "r")


def bound(i, j):
    if 0 <= i < N and 0 <= j < N:
        return True
    return False


def spread():
    i, j = 0, 0
    cnt = 0  # 상어 세기
    while cnt < M:
        if grid[i][j]:
            cnt += 1
            smell[i][j] = [grid[i][j], k]  # (번호, 초)

        j += 1
        if j == N:
            i += 1
            j = 0

def get_moves():
    x, y = 0, 0
    cnt = 0  # 상어 세기
    temp = []

    while cnt < M:
        # 상어일 때
        if grid[x][y]:
            shark = grid[x][y]
            grid[x][y] = 0
            # print(f"shark {shark} at {x} {y}")

            # 각 상어가 이동 방향을 결정할 때는,
            movable = []  # 냄새가 없는 모든 칸으로의 방향
            my_smell = []  # 자신의 냄새가 있는 칸으로의 방향
            for d in range(1, 5):  # 1 위 2 아래 3 왼쪽 4 오른쪽
                nx, ny = x + dx[d], y + dy[d]
                if bound(nx, ny):
                    if smell[nx][ny] == 0:
                        movable.append(d) # 방향
                    if smell[nx][ny] and smell[nx][ny][0] == shark:
                        my_smell.append(d) # 방향
            # print(f"    movable {movable}, mine {my_smell}")
            if movable:
                # 1 먼저 인접한 칸 중 아무 냄새가 없는 칸의 방향으로 잡는다
                search = movable
            else:
                # 2 그런 칸이 없으면 자신의 냄새가 있는 칸의 방향으로 잡는다.
                search = my_smell

            # 이때 가능한 칸이 여러 개일 수 있는데, 그 경우에는 특정한 우선순위를 따른다.
            # 우선순위는 1 상어마다, 2 현재 상어가 보고 있는 방향에 따라 다르다.
            priority = moves[shark][shark_dir[shark]]
            # print(f"{shark}'s priority when {shark_dir[shark]}: {priority}, search={search}")
            for p in priority:
                if p in search:
                    temp.append( [(x + dx[p], y + dy[p]), shark, p] )
                    # print(f"{shark} will move to {temp}")
                    break
            cnt += 1

        y += 1
        if y == N:
            x += 1
            y = 0

    return temp


def update_moves(temp):
    global M
    for (sx, sy), sharknum, prevdir in temp:
        # 상어가 맨 처음에 보고 있는 방향은 입력으로 주어지고,
        # 그 후에는 방금 이동한 방향이 보고 있는 방향이 된다.
        shark_dir[sharknum] = prevdir

        # 모든 상어가 이동한 후 한 칸에 여러 마리의 상어가 남아 있으면,
        # 가장 작은 번호를 가진 상어를 제외하고 모두 격자 밖으로 쫓겨난다.
        if grid[sx][sy]:  # 이미 상어가 있음
            grid[sx][sy] = min(grid[sx][sy], sharknum)
            M -= 1
        else:
            grid[sx][sy] = sharknum


def disappear():
    for i in range(N):
        for j in range(N):
            if smell[i][j]:
                if smell[i][j][1] == 1:
                    smell[i][j] = 0
                else:
                    smell[i][j][1] -= 1


dx = [0, -1, 1, 0, 0]
dy = [0, 0, 0, -1, 1]

T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    # print(f"{test_case} start ---------------------------------\n")

    N, M, k = list(map(int, input().split()))

    grid = [list(map(int, input().split())) for _ in range(N)]
    smell = [[0] * N for _ in range(N)]

    # 방향 1부터 시작하기 위함
    shark_dir = [0] + list(map(int, input().split()))

    moves = [0]
    for i in range(M):
        move = [list(map(int, input().split())) for _ in range(4)]
        moves.append([0] + move)

    time = 0
    while (M > 1):
        # 맨 처음에는 모든 상어가 자신의 위치에 자신의 냄새를 뿌린다.
        spread()
        # 그 후 1초마다 모든 상어가 동시에 상하좌우로 인접한 칸 중 하나로 이동하고, 자신의 냄새를 그 칸에 뿌린다.
        update_moves(get_moves())
        disappear()
        time += 1
        if (time > 1000):
            time = -1
            break
    print(time)
    # print(f"{test_case} end ---------------------------------\n")
'''
상어에는 1 이상 M 이하의 자연수 번호가 붙어 있고, 모든 번호는 서로 다르다.
1의 번호를 가진 어른 상어는 가장 강력해서 나머지 모두를 쫓아낼 수 있다.

N×N 크기의 격자 중 M개의 칸에 상어가 한 마리씩 들어 있다.
맨 처음에는 모든 상어가 자신의 위치에 자신의 냄새를 뿌린다.
그 후 1초마다 모든 상어가 동시에 상하좌우로 인접한 칸 중 하나로 이동하고, 자신의 냄새를 그 칸에 뿌린다.
냄새는 상어가 k번 이동하고 나면 사라진다.

각 상어가 이동 방향을 결정할 때는,
1 먼저 인접한 칸 중 아무 냄새가 없는 칸의 방향으로 잡는다
    이때 가능한 칸이 여러 개일 수 있는데, 그 경우에는 특정한 우선순위를 따른다.
        우선순위는 1 상어마다, 2 현재 상어가 보고 있는 방향에 따라 다르다.
2 그런 칸이 없으면 자신의 냄새가 있는 칸의 방향으로 잡는다.

상어가 맨 처음에 보고 있는 방향은 입력으로 주어지고,
그 후에는 방금 이동한 방향이 보고 있는 방향이 된다.

모든 상어가 이동한 후 한 칸에 여러 마리의 상어가 남아 있으면, 가장 작은 번호를 가진 상어를 제외하고 모두 격자 밖으로 쫓겨난다.
'''
