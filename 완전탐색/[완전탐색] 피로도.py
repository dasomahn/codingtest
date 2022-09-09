# from itertools import permutations        

# def solution(k, dungeons):

#     per = permutations(dungeons, len(dungeons))
#     rounds = []
#     life = k
    
#     for case in per:
#         answer = 0
#         k = life
#         for d in case:
#             if k >= d[0]:
#                 answer += 1
#                 k -= d[1]
#             else:
#                 rounds.append(answer)
#                 break
#         rounds.append(answer)
    
#     return max(rounds)

# DFS solution
answer = 0

def solution(k, dungeons):
    
    N = len(dungeons)
    visited = [0] * N
    
    def dfs(k, cnt):
        global answer
        if cnt > answer:
            answer = cnt

        for j in range(N):
            if k >= dungeons[j][0] and not visited[j]:
                visited[j] = 1
                dfs(k - dungeons[j][1], cnt + 1)
                visited[j] = 0                
                
    dfs(k, 0)
    return answer