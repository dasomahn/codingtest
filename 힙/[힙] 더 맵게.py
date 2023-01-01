def solution(scoville, K):
    answer = 0
    
    while any(s < K for s in scoville):
        if (len(scoville) == 1):
            return -1
        scoville.sort(reverse = True)
        a = scoville.pop()
        b = scoville.pop()
        scoville.append(a + b*2)
        answer += 1
        
    return answer