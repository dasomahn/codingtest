def solution(arr):
    answer = []
    prev = -1
    
    for i in arr:
        if prev == i:
            continue
        else:
            answer.append(i)
            prev = i
    
    return answer

# less var but longer time
def solution(arr):
    answer = [-1]
    for i in arr:
        if i == answer[-1]:
            continue
        else:
            answer.append(i)
    
    return answer[1:]