def solution(n):
    answer = n-1
    
    for i in range(n-2, 1, -1):
        if (n%i == 1):
            answer = i
    
    return answer

# simpler ver.
    return [i for i in range(2, n) if n%i == 1][0]