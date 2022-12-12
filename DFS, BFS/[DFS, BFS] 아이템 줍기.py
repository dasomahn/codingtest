def check_edge(rect, x, y):
    if (rect[0] <= x <= rect[2]) and (rect[1] <= y <= rect[3]):
        return 1
    return 0

def check_line(x1, y1, x2, y2):
    if (abs(x1 - x2) == 2) or (abs(y1 - y2))
        return 1
    return 0

def solution(rectangle, characterX, characterY, itemX, itemY):
    answer = 0
    
    d = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    pre_d = (0, 0)
    change_d = 0
    route = []
    
    while ((characterX != itemX) and (characterY != itemY)):
        # locate 가능한 위치 찾기
        for cur_d in d:
            for rect in rectangle:
                if pre_d == cur_d:
                    continue
                if (check_edge(rect, characterX + cur_d[0], characterX + cur_d[1])):
                    route.append((characterX + cur_d[0], characterX + cur_d[1]))
                    print(route)
                    break
                    
        posX, posY = route.pop()
        # 한개일 경우 (같은 직사각형 이동)
        if !route:
            if pre_d == (posX-characterX, posY-characterY):
                change = pre_d
                pre_d = (posX-characterX, posY-characterY)
            else:
                change =0
            characterX = posX
            characterY = posY
            # update 함수 하나 만들까
        else:
            posX2, posY2 = route.pop()
            if (check_line(posX, posY, posX2, posY2)):
                
        #+2 %4
        
        
        answer += 1

    
    
    return answer