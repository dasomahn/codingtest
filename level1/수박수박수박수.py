def solution(n):
    # pat = "수박"
    # return pat*(n//2)+pat[0]*(n%2)
# one line
    return "수박"*(n//2) + "수"*(n%2)

# or...
    # pat = "수박"*(n//2+1)
    # return pat[:n]