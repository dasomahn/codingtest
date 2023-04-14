import heapq

def solution(gems):
    answer = []
    n = len(gems)
    g = len(set(gems))
    
    dic = {}
    start = 0
    end = 0
    
    while (end < n and start <= end):
        dic[gems[end]] = dic.get(gems[end], 0) + 1
        
        if len(dic) == g:
            while len(dic) == g:
                s = gems[start]

                if dic[s] == 1:
                    del dic[s]
                else:
                    dic[s] -= 1
                start += 1
            
            heapq.heappush(answer, [end-start, start, end+1])
        end += 1

    return([answer[0][1], answer[0][2]])