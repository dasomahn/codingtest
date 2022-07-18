# from itertools import combinations

# def prime(n):
#     for i in range(2, n):
#         if (n%i == 0): return 0
#     return 1


# def solution(nums):
#     answer = 0

#     comb = [sum(i) for i in combinations(nums, 3)]

#     for c in comb:
#         answer += prime(c)

#     return answer

# fixed
from itertools import combinations

def prime(n):
    for i in range(2, int(n**0.5)+1):
        if (n%i == 0): return 0
    return 1
    

def solution(nums):
    return sum([prime(sum(i)) for i in combinations(nums, 3)])