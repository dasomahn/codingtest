def solution(d, budget):
    answer = 0
    temp = 0
    
    for i in sorted(d):
        if (temp+i<=budget):
            temp += i
            answer += 1
        else:
            break            

    return answer

# or
def solution(d, budget):
    answer = 0
    for i in sorted(d):
        budget -= i   
        if (budget<0): break
        answer += 1
            
    return answer