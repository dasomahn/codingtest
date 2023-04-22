def solution(queue1, queue2):
    lst = queue1+queue2
    if sum(lst)%2:
        return -1
    
    n = len(lst)
    target = sum(lst)/2
    
    s, e = 0, n//2
    partsum = sum(queue1)
    
    moves = 0
    while (partsum != target):
        if moves > 1.5*n - 3:
            return -1
        
        if partsum > target:
            partsum -= lst[s]
            s = (s+1)%n
        else:
            partsum += lst[e]
            e = (e+1)%n
        moves += 1
                
    return moves