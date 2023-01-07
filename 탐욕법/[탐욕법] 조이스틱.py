def rotate(list, n):
    return list[n:] + list[:n]

def solution(name):
    size = len(name)
    if name == "A"*size:
        return 0
    
    answer = size
    for i in range(size//2):
        clock = rotate(name, -i)
        c_clock = rotate(name, i+1)[::-1]

        for lst in [clock, c_clock]:
            moves = size-1
            while(moves >= 0 and lst[moves] == 'A'):
                moves -= 1

            answer = min(answer, moves+i)
    
    return answer + sum(min(n-65, 91-n) for n in map(ord, name))

# deque 사용한 풀이
from collections import deque

def calc_moves(name, size):
    moves = size-1
    while(moves >= 0 and name[moves] == 'A'):
        moves -= 1
    
    return moves
    
def solution(name):
    size = len(name)
    
    if name == "A"*size:
        return 0
    
    answer = size
    queue = deque(name)
    
    // 먼저 왼쪽으로 i번 간 후, 시계방향 쭉
    for i in range(size//2):
        answer = min(answer, calc_moves(queue, size) + i)
        queue.rotate(1)
    
    queue = deque(name)
    queue.reverse()
    // 먼저 오른쪽으로 i번 간 후, 반시계방향쭉
    for i in range(size//2):        
        queue.rotate(1)
        answer = min(answer, calc_moves(queue, size) + i)
    
    return answer + sum(min(n-65, 91-n) for n in map(ord, name))
