import sys
sys.stdin = open("15654input.txt", "r")

def dfs(cnt, i):
    if cnt == M:
        print(' '.join(map(str, ans)))
    else:
        for idx in range(i, N):
            ans.append(nums[idx])
            dfs(cnt+1, i)
            ans.pop()

T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    print(f"\n{test_case} start --------------------------------------------------")
    N, M = map(int, input().split())
    nums = list(map(int, input().split()))
    nums.sort()

    ans = []
    dfs(0, 0)

    print(f"\n{test_case} end --------------------------------------------------\n")
