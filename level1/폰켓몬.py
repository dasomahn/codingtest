def solution(nums):
    
    N = len(nums)
    S = len(set(nums))
    
    return S if (S < N/2) else N/2

# diet + fixed
    return min(len(nums)/2, len(set(nums)))