def dfs(visited, start):
    visited.append(start)
    
    for idx in tree[start]:
        if idx not in visited:
            dfs(visited, idx)
            
    return len(visited)
    
def solution(n, wires):
    answer = n - 2
    if n <= 3:
        return answer
    
    global tree
    tree = { i : [] for i in range(1, n+1)}
    
    for a, b in wires:
        tree[a].append(b)
        tree[b].append(a)
    
    for a, b in wires:
        # 전선 끊기
        tree[a].remove(b)
        tree[b].remove(a)
        
        # 첫 번째 노드부터 DFS 돌리기
        l = dfs([], 1)
        answer = min(answer, abs(2*l-n))
        
        # 전선 재연결
        tree[a].append(b)
        tree[b].append(a)
    
    return answer

# Union-find Algorithm
def getParent(parent, i):
    if i == parent[i-1]:
        return i
    return getParent(parent, parent[i-1])

def unionParent(parent, a, b):
    a = getParent(parent, a)
    b = getParent(parent, b)
    parent[max(a, b)-1] = min(a, b)

def solution(n, wires):
    answer = n - 2
    if n <= 3:
        return answer
    
    parent = []
    for cnt in range(n-1):
        parent = [i for i in range(1, n+1)]

        for a, b in wires[:cnt] + wires[cnt+1:]:
            unionParent(parent, a, b)
    
        for i in range(n):
            parent[i] = getParent(parent, i+1)
        
        answer = min(answer, abs(2*parent.count(1)-n))
    
    return answer  