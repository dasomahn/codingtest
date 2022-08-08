def solution(clothes):
    dic = {}
    
    for c in clothes:
        typ = c[1]
        if typ in dic:
            dic[typ] += 1
        else:
            dic[typ] = 2
    
    answer = 1
    for i in dic.values():
        answer *= i
    
    return answer-1

from collections import Counter
from functools import reduce

def solution(clothes):
    counter = Counter(c[1] for c in clothes)
        
    function = lambda x, y: x*(y+1)
    # identical
    def function(x, y):
        return x*(y+1)
        
    return reduce(function, counter.values(), 1)-1

# one line ver.
    return reduce(lambda x, y: x*(y+1), Counter(i[1] for i in clothes).values(), 1)-1