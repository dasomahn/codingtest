def solution(people, limit):
    people.sort(reverse = True)
    
    answer = 0
    i = 0
    j = len(people) - 1
    
    while (i < j):
        M = people[i]
        m = people[j]
        
        if (M + m <= limit):
            j -= 1
        
        i += 1
        answer += 1
            
    if (i==j):
        answer += 1
    
    return answer