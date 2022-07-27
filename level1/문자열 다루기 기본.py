# import re

def solution(s):
    
    # return False if re.search("[\D]", s) else True
    
    # for i in s:
    #     if i not in (range(10)):
    #         return False
    # return True


    # try:
    #     int(s)
    # except ValueError:
    #     return False
    # return True
    
    # return True if s.isdecimal() else False

# answer
    return len(s) in (4, 6) and s.isdecimal()