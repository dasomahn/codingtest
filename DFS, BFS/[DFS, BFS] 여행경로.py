def solution(tickets):
    answer = []
    N = len(tickets)+1
    
    tickets.sort(key=lambda x: x[1])    
    
    def DFS(key, footprint, rem):
        if not rem:
            return footprint

        for idx, (dep, arr) in enumerate(rem):
            if key == dep:
                ret = DFS(arr, footprint+[arr], rem[:idx]+rem[idx+1:])

                if ret:
                    return ret

    return DFS("ICN", ["ICN"], tickets)

# 후위순위 DFS
# def solution(tickets):
#     routes = {}
#     for t in tickets:
#         routes[t[0]] = routes.get(t[0], []) + [t[1]]
#     for r in routes:
#         routes[r].sort(reverse=True)

#     stack = ["ICN"]
#     path = []
#     while len(stack) > 0:
#         top = stack[-1]
#         if top not in routes or len(routes[top]) == 0:
#             path.append(stack.pop())

#         else:
#             stack.append(routes[top][-1])
#             routes[top] = routes[top][:-1]

#     return path[::-1]


# 이상한 DFS 방법
'''
def solution(tickets):
    # tickets.sort(key=lambda x: (x[0], x[1]))
    print(tickets)
    N = len(tickets)+1
    answer = []
    
    def DFS(cur, route, rem):
        if not rem:
            answer.append(route)
        else:
            for idx, (dep, arr) in enumerate(rem):
                if dep == cur:
                    DFS(arr, route+arr, rem[:idx]+rem[idx+1:])

    DFS("ICN", "ICN", tickets)
    answer.sort()
    
    return [ answer[0][i:i+3] for i in range(0, 3*N, 3) ]
'''

# BFS 방법
'''
def solution(tickets):
    tickets.sort(key=lambda x: (x[0], x[1]))
    
    queue = [("ICN", ["ICN"], tickets)]
    
    while(queue):
        cur, route, rem = queue.pop(0)
                
        if not rem:
            return route
        else:
            for idx, (dep, arr) in enumerate(rem):
                if dep == cur:
                    queue.append((arr, route+[arr], rem[:idx]+rem[idx+1:]))
    
    return answer
'''