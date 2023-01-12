def solution(number, k):
    answer = ''
    lst = [n for n in number]
    
    init = len(lst)
    
    i = 0
    while (i < len(lst) - 1) :
        if len(lst) + k == init:
            break
        
        if lst[i] < lst[i+1]:
            lst.remove(lst[i])
        elif lst[i] > lst[i+1]:
            lst.remove(lst[i+1])
        
        i += 1
    
    return ''.join(lst)