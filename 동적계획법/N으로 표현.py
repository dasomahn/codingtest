# n
# nn, 1 op 1
# nnn, 1 op 2, 2 op 1 
# nnnn, 1 op 3, 2 op 2, 3 op 1
# ...
# nn...nn, 1 op N-1, 2 op N-2, ... N-1, 1

def repeat(N, times):
    num = N
    while (times > 1):
        num = num*10 + N
        times -= 1
    return num

def four_op(a, b, s):
    s.add(a + b)
    s.add(a - b)
    s.add(a * b)
    s.add(a / b)

def solution(N, number):
    answer = 1
    
    cases = set()
    while (answer <= 8):
        rep = repeat(N, answer)
        if (rep == answer):
            return answer
        else:
            cases.add(rep)
        
        # 사칙연산        
        for i in range(1, answer):
            four_op(left, right, cases)
            if (number in cases):
                return answer
        
        answer += 1
    
    return -1