def solution(n, results):
    graph = {}
    for a, b in results:
        graph[a] = graph.get(a, []) + [b]
    
    answer = []
    for i in range(1, n):
        cnt = 0
        for node in graph:
            if i == node:
                cnt += 1
            elif i in graph[node]:
                cnt += 1
        if cnt == n-1:
            answer.append(i)
    
    for a in answer:
        answer.extend(graph.get(a, []))
    
    return len(answer)