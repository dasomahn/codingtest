'''
def solution(A, B):
    n = len(A)
    
    A.sort(reverse = True)
    B.sort(reverse = True)
    
    answer = 0
    for a in A:
        i = 0
        while (i < n):
            if avail[i] and a < B[i]:
                avail[i] = 0
                answer += 1
                break
            i += 1
                
    return answer
'''

# fixed
def solution(A, B):
    A.sort(reverse = True)
    B.sort(reverse = True)
    
    idx = 0
    for a in A:
        if a < B[idx]:
            idx += 1
                
    return idx