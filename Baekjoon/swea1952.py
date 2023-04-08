import sys

sys.stdin = open("swea1952input.txt", "r")

T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    day, month, quarter, year = map(int, input().split())
    visit = list(map(int, input().split()))

    dp = [min(visit[i] * day, month) for i in range(12)]
    dp[1] += dp[0]
    dp[2] = min(dp[1] + dp[2], quarter)

    for i in range(3, 12):
        # 1개월로 계속 끊었을 때, 3개월권 썼을 때 비교
        dp[i] = min(dp[i - 1] + dp[i], dp[i - 3] + quarter)

    print(f"#{test_case} {min(dp[11], year)}")
