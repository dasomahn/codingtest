# def getThree(num):
#     return (getThree(num//3) if num > 2 else '') + str(num%3)
    
def solution(n):
       
    # th = getThree(n)
    th = ''
    while(n>0):
        th += str(n%3)
        n //= 3
    # th = th[::-1]
    
    # return sum([int(th[i])*(3**i) for i in range(len(th))])
    return int(th, 3)