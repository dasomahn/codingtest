def solution(brown, yellow):
    total = brown + yellow
    
    for i in range(3, total):
        if total%i == 0:
            if brown == (i*2 + total/i*2)-4:
                return sorted([i, total/i], reverse = True)