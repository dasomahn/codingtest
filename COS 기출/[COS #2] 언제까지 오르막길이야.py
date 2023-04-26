import random
import time

def solution(arr):
    n = len(arr)

    max_len, s = 0, 0
    for e in range(1, n):
        if arr[e-1] < arr[e]:
            max_len = max(max_len, e-s)
        else:
            s = e

    return max_len+1

def solution2(arr):
    dp = [1 for _ in range(len(arr))]
    for i in range(1, len(arr)):
        if arr[i] > arr[i-1]:
            dp[i] = dp[i-1] + 1
    answer = max(dp)
    return answer

sol1, sol2 = 0, 0
for i in range(10):
    print(f"try #{i + 1} ", end=" ")
    length = random.randint(2, 200000)  # 원소 갯수
    arr = random.choices(range(1, 1000001), k=length)  # 원소 수

    start_time = time.time()
    s1 = solution(arr)
    end_time = time.time()
    sol1 += end_time - start_time

    start_time = time.time()
    s2 = solution2(arr)
    end_time = time.time()
    sol2 += end_time - start_time

print(f"\ntime: {sol1 / 10:.6f}")
print(f"time: {sol2 / 10:.6f}")
