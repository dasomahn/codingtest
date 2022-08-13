from itertools import permutations        

def solution(k, dungeons):

    per = permutations(dungeons, len(dungeons))
    rounds = []
    life = k
    
    for case in per:
        answer = 0
        k = life
        for d in case:
            if k >= d[0]:
                answer += 1
                k -= d[1]
            else:
                rounds.append(answer)
                break
        rounds.append(answer)
    
    return max(rounds)