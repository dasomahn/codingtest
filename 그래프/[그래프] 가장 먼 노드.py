from collections import deque

def solution(n, edge):
    dist = [0] * (n+1)
    graph = [[] for _ in range(n+1)]

    
    for a, b in edge:
        graph[a].append(b)
        graph[b].append(a)
        
    queue = deque()
    queue.append(1)
    dist[1] = 1
    
    while queue:
        cur = queue.popleft()
        for g in graph[cur]:
            if dist[g] == 0:
                queue.append(g)
                dist[g] = dist[cur] + 1
    
    return dist.count(max(dist))