def solution(K, words):
    n = len(words)
    
    i = 0
    cnt, line = 1, 0
    while (i < n):
        if line + len(words[i]) <= K:
            line += len(words[i]) + 1
        else:
            cnt += 1
            line = len(words[i])+1
        i += 1

    return cnt