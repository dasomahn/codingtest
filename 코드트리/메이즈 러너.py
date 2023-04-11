import copy
import sys
sys.stdin = open("메이즈 러너input.txt", "r")

def cal_dist(x, y):
    return abs(x-ex)+abs(y-ey)

def bound(x, y):
    if 0 <= x < N and 0 <= y < N:
        return True
    return False

def move():
    global total_moves, M

    for pnum, (px, py) in people.items():
        if px == -1 and py == -1:
            continue
        dist = cal_dist(px, py)
        avail = []
        for dx, dy in dirs:
            nx, ny = px+dx, py+dy
            if bound(nx, ny) and not grid[nx][ny]:
                if dist > cal_dist(nx, ny):
                    avail.append((nx, ny))

        if avail:
            total_moves += 1
            if len(avail) == 1:
                nx, ny = avail[0]
            else:
                if avail[0][1] == py:
                    nx, ny = avail[0]
                else:
                    nx, ny = avail[1]
        else:
            continue

        if nx == ex and ny == ey:
            M -= 1
            people[pnum][0] = -1
            people[pnum][1] = -1
        else:
            people[pnum][0] = nx
            people[pnum][1] = ny

def find():
    w = 1

    while(w):
        for i in range(w+1):
            xrange = (ex-w+i, ex+i)
            if 0 <= xrange[0] < N and 0 <= xrange[1] < N:
                for j in range(w+1):
                    yrange = (ey-w+j, ey+j)
                    if 0 <= yrange[0] < N and 0 <= yrange[1] < N:
                        for pnum, (px, py) in people.items():
                            if px == -1 and py == -1:
                                continue
                            if xrange[0] <= px <= xrange[1] and \
                                yrange[0] <= py <= yrange[1]:
                                return (xrange[0], yrange[0], w)

        w += 1

def rotate(rx, ry, w):
    global ex, ey
    cpy = copy.deepcopy(grid)

    # grid rotate
    for i in range(w + 1):
        for j in range(w + 1):
            if cpy[rx + i][ry + j]:
                grid[rx + j][ry + w - i] = cpy[rx + i][ry + j] - 1
            else:
                grid[rx + j][ry + w - i] = cpy[rx + i][ry + j]

    # exit rotate
    nx = rx-ry+ey
    ny = rx+ry-ex+w
    ex, ey = nx, ny

    # people rotate
    for pnum, (px, py) in people.items():
        if px == -1 and py == -1:
            continue
        if rx <= px <= rx+w and \
                ry <= py <= ry+w:
            people[pnum][0] = rx-ry+py
            people[pnum][1] = rx+ry-px+w


dirs = ((0, 1), (1, 0), (0, -1), (-1, 0))

T = int(input())

# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    print(f"\n{test_case} start ----------------------------------------")

    N, M, K = map(int, input().split())
    grid = [list(map(int, input().split())) for _ in range(N)]

    people = {}
    for i in range(1, M+1):
        people[i] = list(map(int, input().split()))
        people[i][0] -= 1
        people[i][1] -= 1
    ex, ey = map(int, input().split())
    ex, ey = ex-1, ey-1

    total_moves = 0
    while (K > 0):
        move()
        if M == 0:
            break
        rx, ry, w = find()
        rotate(rx, ry, w)

        K -= 1

    print(total_moves)
    print(ex+1, ey+1)
    print(f"{test_case} end ----------------------------------------\n")