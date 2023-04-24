import sys
sys.stdin = open("input/15684input.txt", "r")


# (1, i)가 (N+1, i)로 도착하는지 검사
def climb(l_num, x, y):
    while (x != H+1):
        if grid[x][y] == 1:
            y += 1
        elif grid[x][y] == 2:
            y -= 1
        x += 1

    if l_num == y:
        return l_num
    else:
        return -1


def check():
    for l_num in range(1, W + 1):
        if l_num != climb(l_num, 1, l_num):
            return 0
    return 1


def dfs(x, y, cnt, depth):
    global min_cnt

    if cnt > 3 or cnt >= min_cnt:
        return
    if check():
        min_cnt = cnt
        return

    for i in range(x, H+1):
        if i == x: # 시작했던 줄은 현재 시점부터
            k = y
        else: # 그 다음줄은 맨 처음(왼쪽)부터
            k = 1
        for j in range(k, W):
            if grid[i][j]:
                # 사다리가 있다는 뜻
                continue
            if not grid[i][j] and not grid[i][j+1]:
                grid[i][j] = 1
                grid[i][j + 1] = 2
                dfs(i, j+2, cnt+1, depth+1)  # 두개 넘기기
                grid[i][j] = 0
                grid[i][j + 1] = 0


T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    print(f"\n{test_case} start ---------------------------------------------------------------")

    W, M, H = map(int, input().split())
    if M == 0:
        print("0")
        continue

    grid = [[0] * (W + 2) for _ in range(H + 2)]
    for i in range(M):
        lx, ly = map(int, input().split())
        grid[lx][ly] = 1
        grid[lx][ly+1] = 2

    min_cnt = 4

    dfs(1, 1, 0, 0)

    print("-1" if min_cnt == 4 else min_cnt)
    print(f"{test_case} end ---------------------------------------------------------------\n")
