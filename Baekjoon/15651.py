import sys
sys.stdin = open("input/15649input.txt", "r")

def dfs(l, num):
    ans.append(num)
    if l == M-1:
        print(' '.join(map(str, ans)))

    else:
        for i in range(1, N+1):
            dfs(l+1, i)
    ans.pop()


T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    print(f"\n{test_case} start --------------------------------------------------")
    N, M = map(int, input().split())

    ans = []
    for n in range(1, N+1):
        dfs(0, n)

    print(f"\n{test_case} end --------------------------------------------------\n")

