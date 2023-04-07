def check(idx, num):
    for i in range(1, idx):
        n = board[idx-i]
        if num == n or num == n-i or num == n+i:
            return False
    return True


def dfs(idx):
    global cnt

    if idx == N+1:
        cnt += 1
    else:
        for i in range(1, N + 1):
            board[idx] = i
            if check(idx, i):
                dfs(idx + 1)


N, cnt = int(input()), 0
board = [0] * (N + 1)

dfs(1)
print(cnt)
