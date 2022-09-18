def solution(n, computers):
    answer = 0
    parent = [i for i in range(n)]
    
    def getParent(idx):        
        if parent[idx] != idx:
            return getParent(parent[idx])
        else:
            return idx
    
    ''' fixed
    def unionParent(a, b):
        a = getParent(a)
        b = getParent(b)
        parent[max(a, b)] = min(a, b)
    '''
    
    for idx, c in enumerate(computers):
        for cmp in range(n):
            ''' fixed
            if c[cmp]==1 and idx > cmp:
                parent[idx] = cmp
                parent[idx] = getParent(idx)
            '''
            if c[cmp]==1:
                unionParent(idx, cmp)
    
    for i in range(n):
        parent[i] = getParent(i)
        
    return len(set(parent))