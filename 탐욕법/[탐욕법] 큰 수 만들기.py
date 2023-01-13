def solution(number, k):
    lst = [n for n in number]

    idx = 0
    while (k > 0):
        max_temp = lst[idx:idx+k+2]
        max_idx = idx + max_temp.index(max(max_temp))

        while (k > 0) and (idx != max_idx):
            min_temp = lst[idx:max_idx]
            del lst[idx + min_temp.index(min(min_temp))] # min index로 지우기
            k -= 1
            max_idx -= 1      
        idx = max_idx+1
        
    return ''.join(lst)