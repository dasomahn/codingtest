def solution(x, n):
    try:
        return list(range(x, x*(n+1), x))
    except ValueError:
        return [0]*n
    # return [x*i for i in range(1, n+1)]