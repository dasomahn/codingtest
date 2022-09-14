answer = 25

def solution(maps):
    direction = [(0, 1), (1, 0), (-1, 0), (0, -1)]
    n = len(maps)
    m = len(maps[0])
    
    def move(x, y, visit, cnt):
        global answer
        
        if x==0 and y==0:
            print("arr")
            answer = min(answer, cnt)
            return
        
        if x in [-1, n] or y in [-1, m] or maps[x][y]==0 or visit[x][y]==1:
            print("stp", x, y)
            return
        
        visit[x][y] = 1

        print(x, y, cnt)
        for dx, dy in direction:
            move(x+dx, y+dy, visit, cnt+1)
            
    # visit = [[0]*m]*n
    visit = [[0]*m for _ in range(n)]
    move(n-1, m-1, visit, 1)
        
    return answer if answer != 25 else -1