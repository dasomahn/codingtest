def solution(arr, K):
    arr.sort()
    
    diff = arr[-1]
    for i in range(len(arr)-K+1):
        diff = min(arr[i+K-1]-arr[i], diff)
    
    return diff