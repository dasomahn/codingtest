# def solution(n, lost, reserve):
#     n -= len(lost)

    ''' especially stupid
#     delete = []
#     for val in reserve: # 여벌 체육복이
#         if val in lost: # 도난 당했으면
#             n += 1
#             lost.remove(val)
#             delete.append(val)
    
#     for i in delete:
#         reserve.remove(i)
    '''
    
#     lost.sort()
#     reserve.sort()

#     for i in reserve:
#         if (i-1) in lost:
#             n += 1
#             lost.remove(i-1)
#         elif (i+1) in lost:
#             n += 1
#             lost.remove(i+1)

#     return n

# fixed
def solution(n, lost, reserve):
    
    # new = []
    # for i in reserve:
    #     new.append(i) if i not in lost else lost.remove(i)
    newres = sorted(set(reserve)-set(lost))
    newlost = sorted(set(lost) - set(reserve))
    
    for i in newres:
        if (i-1) in newlost:
            newlost.remove(i-1)
        elif (i+1) in newlost:
            newlost.remove(i+1)
    
    return n - len(newlost)