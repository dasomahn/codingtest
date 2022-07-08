import re

def solution(new_id):    
    answer = new_id.lower()
    answer = re.sub('[^a-z0-9-_.]', '', answer)
    answer = re.sub('[.]{2,}', '.', answer)
    answer = re.sub('^[.]|[.]$', '', answer)
    
    # if len(answer) == 0:
    #     answer = 'a'
    # elif len(answer) >= 16:
    #     answer = answer[:15]
    #     if answer[-1] == '.':
    #           answer = answer[:-1]
    answer = 'a' if len(answer) == 0 else answer [:15]
    answer = re.sub('[.]$', '', answer)
    
    # if len(answer) <= 2:
    #     while(1):
    #         answer += answer[-1]
    #         if len(answer)==3:
    #             break
    answer = answer if len(answer)>2 else answer + answer[-1]*(3-len(answer))

    return answer