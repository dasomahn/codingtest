from collections import deque

def bfs(i, graph):
    queue = deque()
    queue.append(i)
    visited = set()
    
    while(queue):
        cur = queue.popleft()
        visited.add(cur)
        for n in graph[cur]:
            if n not in visited:
                queue.append(n)
    
    return len(visited) - 1

def solution(n, results):
    in_graph = [[] for _ in range(n+1) ]
    out_graph = [[] for _ in range(n+1) ]
    
    for a, b in results:
        in_graph[b].append(a)
        out_graph[a].append(b)
    
    con = [0] * (n+1)
    for i in range(1, n+1):
        con[i] = bfs(i, in_graph) + bfs(i, out_graph)
    
    return con.count(n-1)