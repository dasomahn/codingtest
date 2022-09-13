# cnt = 0

# def solution(numbers, target):
#     N = len(numbers)
    
#     def dfs(exp, i, temp):
#         global cnt
        
#         temp += numbers[i]*(2*exp-1)
#         i += 1
        
#         if i == N:
#             if temp == target:
#                 cnt += 1
#             return
        
#         dfs(1, i, temp)
#         dfs(0, i, temp)
        
#     dfs(1, 0, 0)
#     dfs(0, 0, 0)
            
#     return cnt

# fixed
def solution(numbers, target):
    if not numbers and target == 0 :
        return 1
    elif not numbers:
        return 0
    else:
        return solution(numbers[1:], target-numbers[0]) + solution(numbers[1:], target+numbers[0])
    
# from itertools import product
# def solution(numbers, target):
#     l = [(x, -x) for x in numbers]
#     return list(map(sum, product(*l))).count(target)