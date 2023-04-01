def solution(n, stations, w):
    wave = 2*w+1
    
    cnt = 0
    prev = 1
    for s in stations:
        diff = max(1, s-w) - prev
        if (diff <= 0):
            prev = s+w+1
            continue
            
        cnt += -(-diff//wave)
        prev = s+w+1
        
    diff = n - prev + 1
    if diff > 0:
        cnt += -(-diff//wave)

    return cnt