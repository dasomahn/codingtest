length = 0

def mv_alpha(c):
    return min(c-65, 91-c)

def solution(name):
    global length
    length = len(name)
    
    moves = [0] * length
    
    for idx, c in enumerate(name):
        moves[idx] = mv_alpha(ord(c))
    
    answer = 0
    cur = 0
    while any(m != 0 for m in moves):
        answer += moves[cur]
        moves[cur] = 0
        
        if all(m == 0 for m in moves):
            return answer
        
        left = 1
        while (moves[(cur-left) % length] == 0):
            left += 1
            
        right = 1
        while (moves[(cur+right) % length] == 0):
            right += 1
        print(cur, moves, left, right)
        if (left < right):
            cur = (cur - left) % length
        else:
            cur = (cur + right) % length

        answer += min(left, right)
        
    return answer