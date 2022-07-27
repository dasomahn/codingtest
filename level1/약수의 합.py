def solution(n):
    # answer = 0
    # root = n**0.5
    # for i in range(1, int(root)+1):
    #     if i == root:
    #         answer += i
    #     elif n%i == 0:
    #         answer += i
    #         answer += n//i
    # return answer
    
# one line
    return sum(i for i in range(1, n//2+1) if n%i == 0)+n