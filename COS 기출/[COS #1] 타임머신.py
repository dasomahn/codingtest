'''
def solution(num):
    string = str(num+1).replace("0", "1")
    return int(string)
'''

# fixed
def solution(num):
    num += 1
    digit = 1

    while (num // digit % 10 == 0):
        num += digit
        digit *= 10

    return num