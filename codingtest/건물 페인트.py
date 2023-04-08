def solution(buildings):
    answer = 0

    n = len(buildings)
    m = len(buildings[0])
    view = [[0]*m for _ in range(n)]

    # 좌우
    for i in range(n):
        max_h = 0
        max_h2 = 0
        for b in range(m):
            h = buildings[i][b]
            if max_h < h:
                if view[i][b] == 0:
                    answer += 1
                    view[i][b] = 1
                max_h = max(h, max_h)

            h2 = buildings[i][m-1-b]
            if max_h2 < h2:
                if view[i][m-1-b] == 0:
                    answer += 1
                    view[i][m-1-b] = 1
                max_h2 = max(h2, max_h2)


    # # 위아래
    for i in range(m):
        max_h = 0
        max_h2 = 0

        for b in range(n):
            h = buildings[b][i]
            if max_h < h:
                if view[b][i] == 0:
                    answer += 1
                    view[b][i] = 1                                    
                max_h = max(h, max_h)

            h2 = buildings[n-1-b][i]
            if max_h2 < h2:
                if view[n-1-b][i] == 0:
                    answer += 1
                    view[n-1-b][i] = 1
                max_h2 = max(h2, max_h2)

    return answer