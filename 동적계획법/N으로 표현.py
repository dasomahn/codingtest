# n
# nn, 1 op 1
# nnn, 1 op 2, 2 op 1 
# nnnn, 1 op 3, 2 op 2, 3 op 1
# ...
# nn...nn, 1 op N-1, 2 op N-2, ... N-1, 1

def four_op(a_lst, b_lst, s):
    for a in a_lst:
        for b in b_lst:
            s.append(a + b)
            s.append(a * b)
            if a >= b:
                if (a != b): 
                    s.append(a - b)
                if b != 0:
                    s.append(a // b)
    
def solution(N, number):
    answer = 1
    repeat = 0
    case = {}
    
    while (answer <= 8):
        cases = []
        
        repeat = repeat * 10 + N
        if (repeat == number):
            return answer
        else:
            cases.append(repeat)
        
        # 사칙연산        
        for i in range(1, answer):
            four_op(case[i], case[answer-i], cases)

        set_cases = set(cases)
        if (number in set_cases):
            return answer
        
        case[answer] = set_cases
        answer += 1
    
    return -1