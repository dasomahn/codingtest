def solution(price, money, count):
    answer = price*(count+1)*count/2 - money
    return 0 if answer < 0 else answer

# one line
    return max(0, price*(count+1)*count/2 - money)