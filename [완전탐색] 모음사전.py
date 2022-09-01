# from itertools import product

# def solution(word):
#     dic = []
    
#     for i in range(1, 6):
#         dic += map("".join, product("AEIOU", repeat = i))
    
#     dic.sort()
    
#     return dic.index(word) + 1

# fixed
def solution(word):
    letter = "AEIOU"
    answer = 0

    for n, w in enumerate(word):
        answer += (5**(5-n)-1) / 4 * letter.index(w) + 1
        
    return answer