import random
import time

from itertools import combinations

def solution(arr, K):
    return sum([0 if sum(comb) % K else 1 for comb in combinations(arr, 3)])

def solution2(arr, K):
    n = len(arr)

    answer = 0
    for i in range(n - 2):
        for j in range(i + 1, n - 1):
            for k in range(j + 1, n):
                if not sum([arr[i] + arr[j] + arr[k]]) % K:
                    answer += 1

    return answer

sol1, sol2 = 0, 0
for i in range(10):
    print(f"try #{i + 1} ", end=" ")
    length = random.randint(3, 100)  # 원소 갯수
    arr = random.sample(range(1, 1001), k=length)  # 원소 수
    K = random.randint(1, 10)  # 배수

    start_time = time.time()
    s1 = solution(arr, K)
    end_time = time.time()
    sol1 += end_time - start_time

    start_time = time.time()
    s2 = solution2(arr, K)
    end_time = time.time()
    sol2 += end_time - start_time

print(f"\ntime: {sol1 / 10:.6f}")
print(f"time: {sol2 / 10:.6f}")
