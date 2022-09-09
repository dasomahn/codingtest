# def solution(participant, completion):
#     pdict = {}
    
#     for p in participant:
#         pdict[p] = pdict[p] + 1 if p in pdict else 1
    
#     for c in completion:
#         pdict[c] -= 1
    
#     return sorted(pdict.keys(), reverse=True, key = lambda x: pdict[x])[0]
    
    # failed code
    '''
    for c in completion:
        participant.remove(c)
    return participant[0]
    '''
# fixed 1
# from collections import Counter

# def solution(participant, completion):
#     return list(Counter(participant) - Counter(completion))[0]

# fixed 2
def solution(participant, completion):
    participant.sort()
    completion.sort()
    
    for p, c in zip(participant, completion):
        if p != c:
            return p
    return participant[-1]