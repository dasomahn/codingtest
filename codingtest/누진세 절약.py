import copy, operator

def getCost(arr):
    cost = 0
    for i in range(len(arr)):
        if arr[i]: # 보일러 켜진 날
            if i == 0:
               cost += 1
            else:
                arr[i] += arr[i-1]
                cost += arr[i] # 누진세 계산

    return cost


def solution(boiler):
    ori = boiler.copy()
    ori_cost = getCost(boiler)

    min_day, min_cost = 0, ori_cost

    day = 0
    while day < len(boiler):
        pos = ori[:day] + [1 if not a else 0 for a in ori[day:]]
        cost = getCost(pos)

        if min_cost > cost:
            min_day = day
            min_cost = cost

        day += 1

    return min_day+1 if min_cost != ori_cost else -1