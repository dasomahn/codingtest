def solution(priorities, location):
    point = 0
    N = len(priorities)
    visit = [0]*N
    
    while(visit[location] == 0):
        ch = False
        for i in range(1, N):
            check = (point+i)%N
            if not visit[check] and priorities[check] > priorities[point]:
                point = check
                ch = True
                break
        if i == N-1 and not ch:
            visit[point] = 1
            point = (point+1)%N

    return visit.count(1)