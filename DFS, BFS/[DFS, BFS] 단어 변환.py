def solution(begin, target, words):
    visit = [0]*len(words)
    queue = [(begin, 0)]
    
    '''
    def check(beg, cmp, cnt):
        c = [0 for i, j in zip(beg, cmp) if i!=j]

        if len(c) == 1:
            queue.append((cmp, cnt+1))
            visit[words.index(cmp)] = 1
    '''
    
    # fixed
    def check(beg, cmp, cnt, idx):
        c = 0
        # c += 1 if (i!=j for i, j in zip(beg, cmp)) else 0
        
        for i, j in zip(beg, cmp):
            if i!=j: c += 1
    
        if c == 1:
            queue.append((cmp, cnt+1))
            visit[idx] = 1
        
    while(queue):
        begin, cnt = queue.pop(0)
        if begin == target:
            return cnt
        
        for i, w in enumerate(words):
            if not visit[i]:
                check(begin, w, cnt, i)
                
    return 0