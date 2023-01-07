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