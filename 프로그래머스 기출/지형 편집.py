def solution(land, P, Q):
    answer = -1
    
    h = 0
    while (True):
        plus = 0
        minus = 0
        
        for lan in land:
            for l in lan:
                if l < h:
                    plus += (h-l)
                elif l > h:
                    minus += (l-h)
                    
        cost = plus*P + minus*Q
        answer = cost if answer == -1 else min(answer, cost)
        
        if minus == 0:
            break
        h += 1
    
    return answer