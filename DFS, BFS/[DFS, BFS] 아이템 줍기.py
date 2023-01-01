def check_inner(map, x, y):
    if (map[x][y]):
        if (map[x-1][y] and map[x+1][y] and map[x][y-1] and map[x][y+1] and 
        map[x-1][y-1] and map[x+1][y+1] and map[x+1][y-1] and map[x-1][y+1]):
            return 1
    return 0

def solution(rectangle, charX, charY, itemX, itemY):
    answer = 0
    
    minX = 52
    minY = 52
    maxX = 0
    maxY = 0
    
    for rect in rectangle:
        if (rect[0] < minX):
            minX = rect[0]
        elif (rect[2] > maxX):
            maxX = rect[2]
    
        if (rect[1] < minY):
            minY = rect[1]
        elif (rect[3] > maxY):
            maxY = rect[3]
            
    map = [ [0] * (2*maxY+2) for _ in range(2*maxX+2)]
    inner = [ [0] * (2*maxY+2) for _ in range(2*maxX+2)]
    route = [ [0] * (2*maxY+2) for _ in range(2*maxX+2)]
    
    for rect in rectangle:
        for x in range(2*rect[0], 2*rect[2] + 1):
            for y in range(2*rect[1], 2*rect[3] + 1):
                map[x][y] = 1
                
    for i in range(minX*2, maxX*2):
        for j in range(minY*2, maxY*2):
            if check_inner(map, i, j):
                inner[i][j] = 1
    
    for i in range(minX*2, maxX*2 + 1):
        for j in range(minY*2, maxY*2 + 1):
            route[i][j] = map[i][j] - inner[i][j]

    for i in range(len(map)):
        for j in range(len(map[0])):
            print(route[i][j], end = "")
        print("")

    d = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    charX *= 2
    charY *= 2
    itemX *= 2
    itemY *= 2
    
    # while not((charX == itemX) and (charY == itemY)):
    #     for cur_d in d:
    #         print(charX + cur_d[0],charY + cur_d[1])
    #         if route[charX + cur_d[0]][charY + cur_d[1]]:
    #             answer += 1
    #             break
    #     charX = charX + cur_d[0]
    #     charY = charY + cur_d[1]
    
    return answer
solution([[1, 1, 5, 7]], 1, 1, 4, 7)
