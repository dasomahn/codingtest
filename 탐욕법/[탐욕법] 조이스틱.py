answer = 0

def mv_alpha(c):
    return min(c-65, 91-c)

def getNear(idx):
    left = 1
    while (alp[(idx-left) % length] == 0):
        left += 1
        
    right = 1
    while (alp[(idx+right) % length] == 0):
        right += 1
    
    return (left, right)

def dfs(idx, dist, dir, turnCnt):
    global answer
    print(alp, idx, dist, dir, turnCnt)

    temp = alp[idx]
    alp[idx] = 0
    
    if sum(alp) == 0:
        answer = dist
        return 1

    left, right = getNear(idx)
    if (left < right):
        mv, nxtDir, nxtIdx = left, "left", (idx-left)%length
    else:
        mv, nxtDir, nxtIdx = right, "right", (idx+right)%length
    # print(nxtDir)
    tempTurnCnt = turnCnt
    turnCnt += 0 if dir == nxtDir else 1
    if (turnCnt <= 2 and dfs(nxtIdx, dist+mv, nxtDir, turnCnt)):
        return 1
    
    # 해당 방향이 아닐 때
    if (left > right):
        mv, nxtDir, nxtIdx = left, "left", (idx-left)%length
    else:
        mv, nxtDir, nxtIdx = right, "right", (idx+right)%length
    
    turnCnt = tempTurnCnt if dir == nxtDir else tempTurnCnt + 1
    if (turnCnt <= 2 and dfs(nxtIdx, dist+mv, nxtDir, turnCnt)):
        return 1

    alp[idx] = temp
    turnCnt = tempTurnCnt
    return 0

def solution(name):
    global length, alp, answer
    length = len(name)
    
    if "A"*length == name:
        return 0
    
    alp = [0] * length
    for idx, c in enumerate(name):
        alp[idx] = mv_alpha(ord(c))
    
    dfs(0, sum(alp), None, 0)
    
    return answer