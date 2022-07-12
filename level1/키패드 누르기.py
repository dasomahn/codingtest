# comments are my first try
# def dist(cur, num):
#     cur = cur if cur != 0 else 11
#     num = num if num != 0 else 11
#     ab = abs(cur-num)
    
#     if (ab%3) == 0:
#         dist = ab/3
#     else:
#         if ab == 1: 
#             dist = 1
#         elif ab in [2, 4]:
#             dist = 2
#         elif ab in [5, 7]:
#             dist = 3
#         else:
#             dist = 4
    
#     return dist
    
def solution(numbers, hand):
    answer = ''
    
    # different way
    dic = {
        1:(0, 0), 2:(0, 1), 3:(0, 2),
        4:(1, 0), 5:(1, 1), 6:(1, 2),
        7:(2, 0), 8:(2, 1), 9:(2, 2),
        '*':(3, 0), 0:(3, 1), '#':(3, 2)
          }
    
    # left = 10
    # right = 12
    left = '*'
    right = '#'
    
    for num in numbers:
        if num in [1, 4, 7]:
            answer += "L"
            left = num
        elif num in [3, 6, 9]:
            answer += "R"
            right = num
        else:
            # rightdist = dist(right, num)
            # leftdist = dist(left, num)
            
            rdist = abs(dic[num][0]-dic[right][0]) + abs(dic[num][1]-dic[right][1])
            ldist = abs(dic[num][0]-dic[left][0]) + abs(dic[num][1]-dic[left][1])
            
            if rdist > ldist:
                answer += "L"
                left = num
            elif rdist < ldist:
                answer += "R"
                right = num
            else:
                if hand == "right":
                    answer += "R"
                    right = num
                else:
                    answer += "L"
                    left = num
                    
    return answer