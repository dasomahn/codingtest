'''
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
'''

# fixed
def gcd(a, b):
        res = a%b
        if res == 0:
            return b
        else:
            return gcd(b, res)

def solution(w,h):
    if w > h:
        w, h = h, w
    
    return w*h - h - w + gcd(w, h)