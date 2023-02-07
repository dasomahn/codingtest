dist = []
graph = []

def getParent(a):
    global dist, graph
    
    if a == graph[a]:
        return a
    else:
        return getParent(graph[a])

def union(a, b):
    global dist, graph
    
    a = getParent(a)
    b = getParent(b)
    graph[max(a, b)] = min(a, b)
    
def solution(n, edge):
    global dist, graph
    dist = [0 for i in range(n+1)]
    graph = [i for i in range(n+1)]
    
    for i, (a, b) in enumerate(edge):
        if (a > b):
            edge[i] = [b, a]
    edge.sort()
    
    for a, b in edge:
        union(a, b)
    
    print(graph)
        
    return 0