def solution(arr, divisor):
#     answer = []
    
#     for a in arr:
#         if a%divisor == 0:
#             answer.append(a)
    
#     return sorted(answer) if answer else [-1]

# one line, cleaner
    return sorted([a for a in arr if a%divisor == 0]) or [-1]