def solution(n, m):
#     answer = []
#     l = 1
#     for i in range(2, min(n,m)+1):
#         if (n%i) == 0 and (m%i) == 0:
#             l = i
    
#     return [l, n*m/l]

# Euclidean algorithm
#     def gcd(a, b):
#         res = a%b
#         if res == 0:
#             return b
#         else:
#             return gcd(b, res)
            
#     g = gcd(max(n, m), min(n, m))
    
#     return [g, n*m/g]

# fixed - without function
    a, b = max(n, m), min(n, m)
    while(b):
        a, b = b, a%b
    return [a, n*m/a]