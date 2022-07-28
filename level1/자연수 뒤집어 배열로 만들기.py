def solution(n):
    # return [int(i) for i in str(n)[::-1]]
    return list( map( int, reversed(str(n)) ) )