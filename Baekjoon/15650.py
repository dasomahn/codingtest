import sys
sys.stdin = open("15649input.txt", "r")


def comb2(n, depth):
    if depth == M:
        print(' '.join(map(str, ans)))
    else:
        for i in range(n, N):
            ans[depth] = i + 1
            comb2(i + 1, depth + 1)


def comb1(n, ans, depth):
    if depth == M:
        print(' '.join(map(str, ans)))
    else:
        for i in range(n + 1, N + 1):
            comb1(i, ans + [i], depth + 1)

def dfs(n, depth):
    if depth == M:
        print(' '.join(map(str, ans)))
    else:
        for i in range(n, N):
            visited[i] = 1
            ans.append(i+1)

            dfs(i+1, depth+1)

            ans.pop()
            visited[i] = 0

T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    print(f"\n{test_case} start --------------------------------------------------")
    N, M = map(int, input().split())

    # solution #1
    comb1(0, [], 0)

    # solution #2
    ans = [0] * M
    comb2(0, 0)

    # solution #3
    visited = [0] * (N+1)
    ans = []
    dfs(0, 0)
    print(f"\n{test_case} end --------------------------------------------------\n")
