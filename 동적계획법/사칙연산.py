def solution(arr):
    length = len(arr)
    n = length//2
    
    max_dp = [0]*(n+1)
    min_dp = [0]*(n+1)
    
    while (n > 0):
        num = int(arr[n*2])
        sign = arr[n*2-1]
        
        if n*2 == len(arr)-1:
            num = -(num) if sign == "-" else num
            max_dp[n], min_dp[n] = num, num
        else:
            if sign == '+':
                max_dp[n] = max_dp[n+1] + num
                min_dp[n] = min_dp[n+1] + num
        
            else:
                max_dp[n] = max(-min_dp[n+1], +max_dp[n+1]) -num
                min_dp[n] = min(-max_dp[n+1], +min_dp[n+1]) -num

        n -= 1
    
    return max(max_dp[1], min_dp[1]) + int(arr[0])