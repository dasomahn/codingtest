def solution(n):
    # root = n**0.5
    # return (root+1)**2 if root.is_integer() else -1

    return n == int(n**.5)**2 and (n**.5+1)**2 or -1