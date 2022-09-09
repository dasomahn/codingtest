# def solution(n):
#     def isprime(i):
#         for j in range(2, int(i**0.5)+1):
#             if i % j == 0:
#                 return False
#         return True
    
#     cnt = 0
#     for i in range(2, n+1):
#         cnt += 1 if isprime(i) else 0
#     return cnt

# fixed
def solution(n):
    num=set(range(2,n+1))

    for i in range(2,int(n**0.5)+1):
        if i in num:
            num-=set(range(2*i,n+1,i))
            
    return len(num)