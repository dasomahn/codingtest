def solution(left, right):
    answer = 0
    
    for num in range(left, right+1):        
#         if num == 1:
#             answer -= 1
#         elif num == 2:
#             answer += 2
#         else:            
#             cnt = 2
#             for i in range(2, num//2+1):
#                 if(num % i == 0): 
#                     cnt += 1
#             answer += num if (cnt%2 == 0) else (-num)
        answer += (-num) if (num**0.5).is_integer() else num
    
    return answer