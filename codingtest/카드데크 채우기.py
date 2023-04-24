import copy
from itertools import combinations

def calc(lst):
    point = 0

    prev = -2
    for i in range(len(lst)):
        if lst[i]:
            if i-1 != prev:
                point += i+1
            prev = i

    return point

def solution(n, deck):
    # 들어갈 수 있는 숫자
    poss = set(range(1, n+1)) - set(deck)

    # 데크 자료구조 재구현
    lst = [0] * n
    for d in deck:
        lst[d-1] = 1

    min_point = calc(lst)
    answer = []
    for add in range(1, n-len(deck)+1): # 추가할 카드 수
        c = combinations(poss, add)

        for combi in c:
            ori = lst.copy()
            for num in combi:
                lst[num-1] = 1
            min_point = min(calc(lst), min_point)
            lst = ori

        answer.append(min_point)

    return answer