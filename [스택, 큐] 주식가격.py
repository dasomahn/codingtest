# def solution(prices):
#     answer = []
#     N = len(prices)
    
#     for idx, price in enumerate(prices):
#         for j in range(idx+1, N):
#             if price > prices[j]:
#                 break
#         answer.append(j-idx)
            
#     return answer

# fixed
def solution(prices):
    stack = []
    N = len(prices)
    answer = [0] * N
    
    for i, price in enumerate(prices):
        while stack != [] and stack[-1][1] > price:
            past, _ = stack.pop()
            answer[past] = i - past
        stack.append([i, price])
        
    for i, _ in stack:
        answer[i] = N - 1 - i
        
    return answer