from collections import deque
import sys
sys.stdin = open("input/1260input.txt", "r")

def dfs(V):
    print(V, end = " ")
    visited[V] = 1

    for v in graph[V]:
        if not visited[v]:
            dfs(v)

def bfs(V):
    q = deque([V])
    visited[V] = 1

    while (q):
        V = q.popleft()
        print(V, end=" ")

        for v in graph[V]:
            if not visited[v]:
                visited[v] = 1
                q.append(v)

N, M, V = map(int, input().split())
graph = {i:[] for i in range(1, N+1)}

for _ in range(M):
    v1, v2 = map(int, input().split())
    graph[v1].append(v2)
    graph[v2].append(v1)

for key in graph:
    if graph[key]:
        graph[key].sort()

# dfs
visited = [0] * (N+1)
dfs(V)

print()

# bfs
visited = [0] * (N+1)
bfs(V)

