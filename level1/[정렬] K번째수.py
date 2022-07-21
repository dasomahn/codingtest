def solution(array, commands):
    answer = []
    
    # for com in commands:
    #     answer.append(sorted(array[com[0]-1:com[1]])[com[2]-1])
    
    for i,j,k in commands:
        answer.append(sorted(array[i-1:j])[k-1])
    
    return answer

# one line ver.
    return [sorted(array[i-1:j])[k-1] for i,j,k in commands]