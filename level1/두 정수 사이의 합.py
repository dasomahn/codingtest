def solution(a, b):
    return a if a==b else (a+b)*(abs(a-b)+1)/2

# useable, but more worse
#     if a>b: a, b = b, a
#     return sum(range(a, b+1))