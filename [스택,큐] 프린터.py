# first try
# def solution(priorities, location):
#     point = 0
#     N = len(priorities)
#     visit = [0]*N
    
#     while(visit[location] == 0):
#         ch = False
#         for i in range(1, N):
#             check = (point+i)%N
#             if not visit[check] and priorities[check] > priorities[point]:
#                 point = check
#                 ch = True
#                 break
#         if i == N-1 and not ch:
#             visit[point] = 1
#             point = (point+1)%N

#     return visit.count(1)

# second try
# def solution(priorities, location):
#     queue = [(i, p) for i, p in enumerate(priorities)]
#     cnt = 0
    
#     while True:
#         check = queue.pop(0)
#         if any(check[1] < cmp[1] for cmp in queue):
#             queue.append(check)
#         else:
#             cnt += 1
#             if check[0] == location:
#                 return cnt

# third try
# def solution(priorities, location):
#     cnt = 0
#     queue = [(p, i) for i, p in enumerate(priorities)]
    
#     m = max(q[0] for q in queue)
#     while (queue):
#         if queue[0][0] == m:
#             cnt += 1
#             if queue[0][1] == location:
#                 return cnt
#             queue.pop(0)
#             m = max(q[0] for q in queue)
            
#         else:
#             while(queue[0][0] != m):
#                 queue.append(queue.pop(0))
#                 # slicing 보다 pop & append가 더 빠르겠지?

# last try
def solution(priorities, location):
    point = 0
    cnt = 0
    N = len(priorities)
    
    m = max(priorities)
    while True:
        if (m == priorities[point]):
            cnt += 1
            if point == location:
                return cnt
            priorities[point] = 0
            m = max(priorities)
            
        else:
            idx = priorities.index(m)
            if idx < point:
                point = (point+1)%N
            else:
                point = idx