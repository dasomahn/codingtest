'''
def solution(cookie):
    answer = 0
    n = len(cookie)
    
    for l in range(n-1):
        s1 = 0
        for m in range(l, n-1):
            s1 += cookie[m] # l ~ m
            
            s2 = 0
            for r in range(m+1, n):
                s2 += cookie[r] # m+1 ~ r
                
                if s1 == s2:
                    answer = max(answer, s1)
    
    return answer
'''

# fixed
def solution(cookie):
    answer = 0
    M = sum(cookie) // 2 + 1
    n = len(cookie)
    
    for m in range(n-1):
        l, sum_l = m, cookie[m]
        r, sum_r = m+1, cookie[m+1]
        
        while (sum_l < M and sum_r < M):
            if (sum_l == sum_r):
                answer = max(answer, sum_l)
                
            if (l > 0 and sum_l <= sum_r):
                l -= 1
                sum_l += cookie[l]
            elif (r < n-1 and sum_l >= sum_r):
                r += 1
                sum_r += cookie[r]
            else:
                break

    return answer