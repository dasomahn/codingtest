def solution(genres, plays):
    answer = []
    dic = { g:[] for g in set(genres)}
    
    for i, genre in enumerate(genres):
        dic[genre].append( (plays[i], i) )
        
    # sort_dic = dict(sorted(dic.items(), key = lambda x: sum(i[0] for i in x[1]), reverse = True))
    sort_dic = sorted(dic.values(), key = lambda x: sum(i[0] for i in x), reverse = True)
    
    # for val in sort_dic.values():
    for val in sort_dic:
        # temp = sorted(val, key = lambda x: (x[0], -x[1]), reverse = True)
        temp = [e[1] for e in sorted(val, key = lambda x: (x[0], -x[1]), reverse = True)]
        
#         answer.append(temp[0][1])
#         if len(temp) >= 2:
#             answer.append(temp[1][1])
        answer += temp[:2]
            
    return answer