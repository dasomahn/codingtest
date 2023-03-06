'''
ex1) 1 3 1 2 1
(= 는 다음 자리를 의미)
1 = - - - (1 자체)
1 3 = - - (3 자체)
1 3 3 = - (직전 3 vs 전전1 + 방문1 -> 전자 3)
1 3 3 5 = (직전 3 vs 전전3 + 방문2 -> 5)

ex2) 1 3 1 1 6 1
1 = - - - -
1 3 = - - -
1 3 3 = - - (직전 3 vs 전전1 + 방문1 -> 전자 3)
1 3 3 4 = - (직전 3 vs 전전3 + 방문1 -> 후자 4)
1 3 3 4 9 = (직전 4 vs 전전3 + 방문6 -> 후자 9)
1 3 3 4 9 9 (직전 9 vs 전전4 + 방문1 -> 전자 9)

'''

def cal(money, n):
    dp = [0] * n
    
    for i in range(n):
        if i in (0, 1):
            dp[i] = money[i]
        dp[i] = max(dp[i-1], dp[i-2] + money[i])
    
    return (dp[n-1])

def solution(money):
    n = len(money)
    
    a = cal(money[:-1], n-1)
    b = cal(money[1:], n-1)
    
    return max(a, b)