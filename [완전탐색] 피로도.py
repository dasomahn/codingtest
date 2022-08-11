def solution(k, dungeons):
    answer = 0
    
    length = len(dungeons)
    dungeons.sort(key=lambda x: (-x[0], x[1]))
    for d in dungeons:
        if k>=d[0]:
            answer += 1
            k -= 20
        else:
            return answer
    
    return answer