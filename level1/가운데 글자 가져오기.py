def solution(s):
    l = len(s)
    if l%2 != 0:
        return s[l//2]
    else:
        return s[l//2-1:l//2+1]

# one line
    return s[(len(s)-1)//2:len(s)//2+1]