# def solution(citations):
#     for i in range(max(citations), min(citations)-1, -1):
#         print(i)
#         cnt = 0 # 논문 편수
#         for c in citations:
#             if c >= i:
#                 cnt += 1
#         if cnt >= i:
#             return i
#     return len(citations)

# def solution(citations):
#     citations.sort(reverse = True)
    
#     n = len(citations)
#     for h in range(n, -1 ,-1):
#         if citations[h-1] >= h:
#             return h
        
def solution(citations):
    citations.sort(reverse=True)
    return max(map(min, enumerate(citations, start=1)))
