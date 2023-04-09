import sys
sys.stdin = open("15665input.txt", "r")

def dfs(l):
    if l == M:
        total.append(ans.copy())
    else:
        prev = 0
        for i in range(N):
            if prev != nums[i]:
                prev = nums[i]
                ans.append(nums[i])
                dfs(l+1)
                ans.pop()


T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    print(f"\n{test_case} start --------------------------------------------------")
    N, M = map(int, input().split())
    nums = list(map(int, input().split()))
    nums.sort()

    total = []
    ans = []
    dfs(0)
    for t in total:
        print(' '.join(map(str, t)))

    print(f"\n{test_case} end --------------------------------------------------\n")

