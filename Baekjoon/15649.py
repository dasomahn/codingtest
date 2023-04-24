import sys
sys.stdin = open("input/15649input.txt", "r")


def perm(nums, ans, depth):
    if depth == M:
        print(' '.join(map(str, ans)))
    else:
        for i, n in enumerate(nums):
            perm(nums[:i] + nums[i + 1:], ans + [n], depth + 1)


def dfs(depth):
    if depth == M:
        print(' '.join(map(str, ans)))
    else:
        for i in range(1, N + 1):
            if not visited[i]:
                visited[i] = 1
                ans.append(i)

                dfs(depth + 1)

                # 백트래킹
                visited[i] = 0
                ans.pop()


T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    print(f"\n{test_case} start --------------------------------------------------")
    N, M = map(int, input().split())

    # solution #1
    nums = list(range(1, N + 1))
    perm(nums, [], 0)

    # solution #2
    visited = [0] * (N + 1)
    ans = []
    dfs(0)
    print(f"\n{test_case} end --------------------------------------------------\n")
