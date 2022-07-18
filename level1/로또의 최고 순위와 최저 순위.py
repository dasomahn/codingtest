def solution(lottos, win_nums):
    # answer = []
    rank = [6, 6, 5, 4, 3, 2, 1]
    
    zeros = lottos.count(0)
    lot = 0
    for l in lottos:
        if l in win_nums:
            lot += 1
    
    # maxlot = lot + lottos.count(0)

    # answer.append((7 - maxlot) if maxlot>1 else 6)
    # answer.append((7 - lot) if lot>1 else 6)
    
    # return answer
    return rank[lot+zeros], rank[lot]