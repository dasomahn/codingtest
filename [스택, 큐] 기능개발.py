# import math
# def solution(progresses, speeds):
#     N = len(progresses)
#     days = []
    
#     for p, s in zip(progresses, speeds):
#         days.append(math.ceil((100-p)/s))
    
#     release = []
#     i = 0
#     cnt = 1
    
#     while i <= (N-1):
#         cnt = 1
#         compare = days[i]
#         i += 1
        
#         while( i != N and compare >= days[i]):
#             i += 1
#             cnt += 1
        
#         release.append(cnt)
        
#     return release
        
# fixed
def solution(progresses, speeds):
    Q=[]
    
    for p, s in zip(progresses, speeds):
        if not Q or Q[-1][0] < -((p-100)//s):
            Q.append([-((p-100)//s), 1])
        else:
            Q[-1][1] += 1
            
    return [q[1] for q in Q]