'''
7 14 21 28 35 ...
10 20 30 40 50 ...

-> 7 10 14 20 21 28

sort()가 시간초과가 나니 다른 정렬법 사용해야 함
'''

def solution(n, times):
    left = 1
    right = max(times) * n

    answer = 0
    while left < right:
        mid = (left + right) // 2
        people = 0
        for time in times:
            people += mid // time
            
        if people >= n:
            right = mid
        else:
            left = mid + 1
    answer = left

    return answer