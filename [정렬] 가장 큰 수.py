from functools import cmp_to_key

def sort_fuc(x, y):
#     s_x = str(x)
#     s_y = str(y)
    
#     if s_x[0] > s_y[0]:
#         return -1
#     elif s_x[0] < s_y[0]:
#         return 1
#     else:
# #         s_x[0] == s_y[0]
#         left = int(s_x + s_y)
#         right = int(s_y + s_x)
        
#         if left > right:
#             return -1
#         elif left < right:
#             return 1
#         else:
#             return 0

# cleaner
    left = int(x+y)
    right = int(y+x)
    
    if left > right:
        return -1
    elif left < right:
        return 1
    else:
        return 0

def solution(numbers):
#     sort = sorted(numbers, key = cmp_to_key(sort_fuc))
#     return(str(int(''.join(str(i) for i in sort))))    
                
    numbers = [str(i) for i in numbers]
    sort = sorted(numbers, key = cmp_to_key(sort_fuc))
                
    return(str(int(''.join(sort))))   

# simpler & faster    
# def solution(numbers):
#     numbers = list(map(str, numbers))
#     numbers.sort(key=lambda x: x*3, reverse=True)
#     return str(int(''.join(numbers)))