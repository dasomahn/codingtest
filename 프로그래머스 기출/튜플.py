'''
def solution(s):
    answer = []
    
    arr = s[2:-2].split("},{")
    arr.sort(key=lambda x:len(x))
    
    for a in arr:
        lst = list(map(int, a.split(",")))
        for l in lst:
            if l not in answer:
                answer.append(l)
                break
    
    return answer
'''

# fixed
def solution(s):
    dic = {}

    arr = s[2:-2].split("},{")
    for a in arr:
        lst = list(map(int, a.split(",")))
        for l in lst:
            dic[l] = dic.get(l, 0) + 1

    return [k for k in sorted(dic.keys(), key=lambda x: dic[x], reverse=True)]