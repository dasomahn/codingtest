def solution(n, stations, w):
    lst = [0] * (n+1)
    
    for s in stations:
        for i in range(s-w, s+w+1):
            if i > n: break
            lst[i] = 1
    
    cnt = 0
    for i in range(1, n+1):
        if lst[i]:
            continue
        
        if i+w > n:
            cnt += 1
            break
        for j in range(i, i+w*2+1):
            if j > n: break
            lst[j] = 1        
        cnt += 1
        
    return cnt