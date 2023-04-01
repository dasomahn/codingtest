def solution(land, P, Q):
    length = len(land) ** 2
    total = 0
    
    dic = {}
    for lan in land:
        for l in lan:
            dic[l] = dic.get(l, 0) + 1
            total += l
    
    # (0층부터 시작 가정)
    prev = 0 # 직전 층 (0층)
    cost = total*Q # 직전 단계 값 저장 (0층에서의 값)
    n = 0 # 해당 층보다 낮은 블록의 갯수
    
    answer = cost # 정답 변수
    
    for h in sorted(dic.keys()):
        cost = cost + (n*P - (length-n)*Q) * (h-prev)
            
        if (answer < cost):
            break
        answer = cost
        
        n += dic[h]
        prev = h
    
    return answer