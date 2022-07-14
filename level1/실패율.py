def solution(N, stages):
    user = float(len(stages))
    fail = [0]*N

    for i in range(1, N+1): # from 1 to N
        if user == 0: break # fixed !

        num = stages.count(i)
        if num != 0:
            fail[i-1] = num/user
            user -= num

    answer = sorted(range(1, len(fail)+1), key = (lambda x: fail[x-1]), reverse = True)

    return answer

