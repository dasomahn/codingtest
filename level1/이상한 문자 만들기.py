def solution(s):
    answer = []
    split = s.split(" ")
    
    for i in range(len(split)):
        for idx, l in enumerate(split[i]):
            if idx%2:
                answer += l.lower()
            else:
                answer += l.upper()
        if i == len(split)-1:
            break
        answer += " "
    return answer

# one line ver.
    return " ".join(map(lambda x: 
                        "".join([a.lower() if i % 2 else a.upper() for i, a in enumerate(x)])
                        , s.split(" ")))