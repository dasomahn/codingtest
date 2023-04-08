import sys

sys.stdin = open("1182input.txt", "r")


def comb(n, total, depth):
    global cnt, idx

    if depth and total == S:
        cnt += 1
    elif depth == N + 1:
        return

    for i in range(n, N):
        comb(i + 1, total + nums[i], depth + 1)


T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    print(f"-----------{test_case}-----------start")
    N, S = map(int, input().split())
    nums = list(map(int, input().split()))

    cnt = 0
    comb(0, 0, 0)
    print(cnt)
    print(f"-----------{test_case}-----------end")
