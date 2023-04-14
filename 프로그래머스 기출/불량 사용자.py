N = 0
answer = []

def match(user, ban):
    for u, b in zip(user, ban):
        if b == '*':
            continue
        elif u != b:
            return False
    return True

def dfs(user_id, banned_id, idx, matched, n):
    for idx in range(idx, N):
        for i, b in enumerate(banned_id):
            if not matched[i]:
                u = user_id[idx]
                if len(u) == len(b) and match(u, b):
                    matched[i] = u
                    dfs(user_id, banned_id, idx+1, matched, n+1)
                    matched[i] = 0
    
    if n == len(banned_id):
        if set(matched) not in answer:
            answer.append(set(matched))

def solution(user_id, banned_id):
    global N
    N = len(user_id)
    
    matched = [0] * len(banned_id)
    dfs(user_id, banned_id, 0, matched, 0)
    
    return(len(answer))