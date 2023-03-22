def solution(w,h):
    if w > h:
        w, h = h, w
    
    gcd = 1
    for i in range(1, w+1):
        if w%i == 0 and h%i == 0:
            gcd = i
            
    w2 = w/gcd
    h2 = h/gcd
    
    return w*h - ((h2 - 1 + w2) * gcd)