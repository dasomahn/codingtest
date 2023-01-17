# def inRange(ranges, x):
#     if ranges[0] <= x and x <= ranges[1]:
#         return 1
#     return 0

# def solution(routes):
#     routes.sort()
#     stack = []
    
#     for i, o in routes:
#         flag = 0
#         for idx, s in enumerate(stack):
#             if inRange(s, i) or inRange(s, o) in s:
#                 flag = 1
#                 i = max(s[0], i)
#                 o = min(s[1], o)
#                 stack[idx] = [i, o]
#                 break
        
#         if not flag:
#             stack.append([i, o])
    
#     return len(stack)

# fixed
def solution(routes):
    routes.sort(key=lambda x:x[1])
    answer = 0
    last_cam = -30000
    
    for i, o in routes:
        if i > last_cam:
            last_cam = o
            answer += 1
    
    return answer