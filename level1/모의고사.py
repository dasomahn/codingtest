# def solution(answers):
#     answer = []
#     dic = {1:0, 2:0, 3:0}
    
#     n = len(answers)
#     mul = ((n+1)//5 + 1)
    
#     check = [(list(range(1, 6))*mul)[:n], 
#              ([2, 1, 2, 3, 2, 4, 2, 5]*mul)[:n], 
#              ([3, 3, 1, 1, 2, 2, 4, 4, 5, 5]*mul)[:n]
#             ]
    
#     for i in range(n):
#         for j in [1, 2, 3]:
#             dic[j] += 1 if (answers[i] == check[j-1][i]) else 0

#     m = max(dic.values())
#     for key, value in dic.items():
#         if value == m:
#             answer.append(key)
    
#     return sorted(answer)

# fixed
def solution(answers):
    dic = {1:0, 2:0, 3:0}
    
    p1 = [1, 2, 3, 4, 5]
    p2 = [2, 1, 2, 3, 2, 4, 2, 5]
    p3 = [3, 3, 1, 1, 2, 2, 4, 4, 5, 5]
    
    # check = [p1, p2, p3]
    # for idx, val in enumerate(answers):
    #     for i, v in enumerate(check):
    #         dic[i+1] += 1 if (val == v[idx%len(v)]) else 0
    # but the code below is faster
    for i in range(len(answers)):
        if answers[i] == p1[i%len(p1)]:
            dic[1] += 1
        if answers[i] == p2[i%len(p2)]:
            dic[2] += 1
        if answers[i] == p3[i%len(p3)]:
            dic[3] += 1
    
    return [key for key, value in dic.items() if value == max(dic.values())]