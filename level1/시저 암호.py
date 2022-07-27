# def solution(s, n):
#     answer = ''
#     for i in s:
#         if i == " ":
#             answer += " "
#         else:
#             cal = ord(i)+n
#             if i.islower():
#                 if cal > ord("z"):
#                     cal -= 26
#             else:
#                 if cal > ord("Z"):
#                     cal -= 26
#             answer += chr(cal)
                
#     return answer

# fixed
def solution(s, n):
    answer = ""
    for i in s:
        if i == " ":
            answer += " "
        elif i.islower():
            answer += chr( ord("a")+ (ord(i)+n-ord("a"))%26 )
        else:
            answer += chr( ord("A")+ (ord(i)+n-ord("A"))%26 )
    return answer