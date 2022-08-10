def isPrime(num):
    if num == 0 or num == 1:
        return False
    for i in range(2, int(num**0.5)+1):
        if num%i == 0:
            return False
    return True

# from itertools import permutations

def makeP(ori, rem, cases):
    if ori != "":
        cases.append(ori)
    for i in range(len(rem)):
        makeP(ori+rem[i], rem[:i]+rem[i+1:], cases)

def solution(numbers):
    answer = 0
    cases = []
# with itertools
    # for i in range(1, len(numbers)+1):
    #     cases += map("".join, set(permutations(numbers, i)))
    
# without itertools    
    makeP("", numbers, cases)
    setcase = set(map(int, cases)) - {0, 1}

    for case in setcase:
        answer += 1 if isPrime(case) else 0

    return answer

# Sieve of Eratosthenes
#     M = max(setcase)
#     for idx in range(2, int(M**0.5)+1):
#         setcase -= set(range(idx*2, M+1, idx))
    
#     return len(setcase)