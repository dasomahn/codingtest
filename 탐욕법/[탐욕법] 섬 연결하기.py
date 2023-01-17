def getParent(p, i):
    if i == p[i]:
        return i
    return getParent(p, p[i])
    
def union(p, a, b):
    a = getParent(p, a)
    b = getParent(p, b)
    if a == b:
        return -1
    p[max(a, b)] = min(a, b)

def solution(n, costs):
    costs.sort(key=lambda x:x[2])
    
    answer = 0
    parent = [i for i in range(n)]
    
    for a, b, c in costs:
        if union(parent, a, b) == -1:
            continue
            
        answer += c
        n -= 1

        if n == 1:
            return answer