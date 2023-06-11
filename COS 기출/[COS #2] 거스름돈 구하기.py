def solution(money):
    coin = [50000, 10000, 5000, 1000, 500, 100, 50, 10]

    count = 0
    for c in coin:
        count += money // c
        money %= c
    return count
