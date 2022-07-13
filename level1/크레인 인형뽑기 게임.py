# def solution(board, moves):
#     answer = 0  
#     res = []

#     for m in moves:
#         for row in board:
#             if row[m-1] != 0:
#                 # print("뽑았다, ", row[m-1],"번!")
#                 res.append(row[m-1])
#                 row[m-1] = 0
#                 break

#     i = len(res) - 1
#     while(i>0):
#         if res[i] == res[i-1]:
#             answer += 2
#             del res[i-1]
#             del res[i-1]
#         i -= 1

#     return answer

# fixed

def solution(board, moves):
    answer = 0  
    res = [0]
    
    for m in moves:
        for row in board:
            if row[m-1] != 0:
                row[m-1] = 0
                
                if res[-1] == row[m-1]:
                    answer += 2
                    res.pop()
                else:
                    res.append(row[m-1])
                    
                break
    
    return answer