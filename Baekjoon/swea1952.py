import sys

sys.stdin = open("input/swea1952input.txt", "r")


def dfs(idx, cost):
    global min_cost

    if idx >= 12:
        min_cost = min(min_cost, cost)
    else:
        dfs(idx + 1, cost + visit[idx] * day)
        dfs(idx + 1, cost + month)
        dfs(idx + 3, cost + quarter)


T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    day, month, quarter, year = map(int, input().split())
    visit = list(map(int, input().split()))

    # 풀이 1 DP
    dp = [min(visit[i] * day, month) for i in range(12)]
    dp[1] += dp[0]
    dp[2] = min(dp[1] + dp[2], quarter)

    for i in range(3, 12):
        # 1개월로 계속 끊었을 때, 3개월권 썼을 때 비교
        dp[i] = min(dp[i - 1] + dp[i], dp[i - 3] + quarter)

    print(f"#{test_case} {min(dp[11], year)}")

    # 풀이 2 DFS
    min_cost = year
    dfs(0, 0)

    print(f"#{test_case} {min_cost}")
