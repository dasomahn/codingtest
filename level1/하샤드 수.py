def solution(x):
    # return False if x%(sum(int(i) for i in str(x))) else True
    return x%(sum(int(i) for i in str(x))) == 0