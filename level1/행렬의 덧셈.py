def solution(arr1, arr2):    
#     answer = []
#     for one, two in zip(arr1, arr2):
#         temp = []
#         for i, j in zip(one, two):
#             temp.append(i+j)
#         answer.append(temp)
    
#     return answer

# one line
    return [[c+d for c, d in zip(a, b)] for a, b in zip(arr1, arr2)]