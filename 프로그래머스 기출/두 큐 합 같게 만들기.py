from collections import deque

def solution(queue1, queue2):
    lst = queue1+queue2
    if sum(lst)%2:
        return -1
    
    n = len(lst)
    target = sum(lst)/2
    
    q = deque([(0, n//2, 0, sum(queue1))])
    
    while (q):
        s, e, moves, partsum = q.popleft()
        
        if moves > 1.5*n - 3:
            return -1
        
        if partsum == target:
            return moves
        else:
            if partsum > target:
                q.append([(s+1)%n, e, moves+1, partsum-lst[s]])
            else:
                q.append([s, (e+1)%n, moves+1, partsum+lst[e]])