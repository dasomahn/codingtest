def solution(num):
#     cnt = 0

#     if num == 1: return cnt
    
#     while(cnt < 500):
#         if num%2 == 0:
#             num /= 2
#         else:
#             num = num*3 + 1
#         cnt += 1
#         if num==1:
#             return cnt
#     return -1

# fixed
    for i in range(500):
        if num == 1:
            return i
        num = num*3+1 if num%2 else num/2
    return -1