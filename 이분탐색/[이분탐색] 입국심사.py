'''
7 14 21 28 35 ...
10 20 30 40 50 ...

-> 7 10 14 20 21 28

sort()가 시간초과가 나니 다른 정렬법 사용해야 함
'''

def solution(n, times):
    cases = []
    
    for i in range(1, n):
        for t in times:
            cases.append(t*i)
    
    cases.sort()
            
    return cases[n-1]