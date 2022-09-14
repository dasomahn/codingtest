answer = 25

def solution(maps):
    direction = [(0, 1), (1, 0), (-1, 0), (0, -1)]
    n = len(maps)
    m = len(maps[0])
    
    def bfs(x, y):
        visit = []
        queue = []
        cnt = 0
        
        queue.append((x, y))
        
        while queue:
            nx, ny = queue.pop(0)
            if (nx, ny) == (0, 0):
                return answer
            
            if nx in [-1, n] or ny in [-1, m] or (nx, ny) in visit or maps[nx][ny]==0:
                print("stp", nx, ny, queue)
                continue
            
            print(nx, ny, queue)
            visit.append((nx, ny))
            for dx, dy in direction:
                queue.append((x+dx, y+dy))
        
        return -1
            
    bfs(n-1, m-1)
        

'''
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
        
        if x in [-1, n] or y in [-1, m] or maps[x][y]==0 or (x,y) in visit:
            print("stp", x, y, visit)
            return
        
        visit.append((x, y))

        print(x, y, cnt)
        for dx, dy in direction:
            move(x+dx, y+dy, visit, cnt+1)
            
    # visit = [[0]*m]*n
    move(n-1, m-1, [], 1)
        
    return answer if answer != 25 else -1
'''