def solution(s):
    answer = []
    
    arr = s[2:-2].split("},{")
    arr.sort(key=lambda x:len(x))
    
    for i, a in enumerate(arr):
        arr[i] = list(map(int, a.split(",")))
    
    for lst in arr:
        for l in lst:
            if l not in answer:
                answer.append(l)
                break
    
    return answer