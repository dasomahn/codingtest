import sys
sys.stdin = open("input/15654input.txt", "r")
def dfs(l, idx):
    if l == M:
        print(' '.join(map(str, ans)))
    else:
        for i in range(idx, N):
            ans.append(nums[i])
            dfs(l+1, i+1)
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
