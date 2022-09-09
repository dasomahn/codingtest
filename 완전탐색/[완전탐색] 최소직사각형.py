def solution(sizes):
    answer = 1
    for each in sizes:
        each.sort()

    for x in zip(*sizes):        
        answer *= max(x)
    
    return answer

# other ver1.
def solution(sizes):
    return max(max(x) for x in sizes) * max(min(x) for x in sizes)

# other ver2.
def solution(sizes):
    M = set()
    m = set()
    
    for x in sizes:
        M.add(max(x))
        m.add(min(x))
        
    return max(M)*max(m)