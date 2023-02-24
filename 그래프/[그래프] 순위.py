'''
from collections import deque

def bfs(i, graph):
    queue = deque()
    queue.append(i)
    visited = set()
    
    while(queue):
        cur = queue.popleft()
        visited.add(cur)
        for n in graph[cur]:
            if n not in visited:
                queue.append(n)
    
    return len(visited) - 1

def solution(n, results):
    in_graph = [[] for _ in range(n+1) ]
    out_graph = [[] for _ in range(n+1) ]
    
    for a, b in results:
        in_graph[b].append(a)
        out_graph[a].append(b)
    
    con = [0] * (n+1)
    for i in range(1, n+1):
        con[i] = bfs(i, in_graph) + bfs(i, out_graph)
    
    return con.count(n-1)
'''

# fixed
from collections import defaultdict

def solution(n, results):
    win, lose = defaultdict(set), defaultdict(set)
    
    for winner, loser in results:
            lose[loser].add(winner)
            win[winner].add(loser)

    for i in range(1, n+1):
        for winner in lose[i]:
            win[winner].update(win[i])
        for loser in win[i]:
            lose[loser].update(lose[i])

    answer = 0
    for i in range(1, n+1):
        if len(win[i]) + len(lose[i]) == (n - 1):
            answer += 1
    
    return answer

# floyd-warshall
def solution(n, results):
    board = [[0] * n for _ in range(n)]
    
    # p1 > p2는 1, p1 < p2는 -1로 초기화
    for p1, p2 in results:
        board[p1 - 1][p2 - 1] = 1       # win
        board[p2 - 1][p1 - 1] = -1      # lose

    for k in range(n): # k: 경유점
        for i in range(n):
            for j in range(n):
                if board[i][k] == 1 and board[k][j] == 1:
                    board[i][j] = 1     # 만약 i > k이고, k > j라면 i > j
                elif board[i][k] == -1 and board[k][j] == -1:
                    board[i][j] = -1    # 만약 i < k이고, k < j라면 i < j

    # 각 노드 점수판에 0이 하나인 경우 판별
    # 즉, 다른 노드들에 대해 승패가 모두 결정되었다는 의미
    answer = 0
    for i in range(n):
        if board[i].count(0) == 1:
            answer += 1

    return answer