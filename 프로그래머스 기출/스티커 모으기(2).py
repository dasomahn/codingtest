def case(sticker, n):
    dp = [0] * (n-1)
    
    for i in range(n-1):
        if i == 0:
            dp[i] = sticker[i]
        elif i == 1:
            dp[i] = max(dp[i-1], sticker[i])
        else:
            dp[i] = max(dp[i-1], dp[i-2] + sticker[i])
            
    return dp[-1]

def solution(sticker):
    n = len(sticker)
    if (n == 1):
        return sticker[0]
    
    return max(case(sticker[:-1], n), case(sticker[1:], n))