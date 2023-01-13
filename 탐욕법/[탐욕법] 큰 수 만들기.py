'''
def remove(string, idx):
    return string[:idx] + string[idx+1:]

def get_min(string, start, end):
    num = "0123456789"
    for n in num:
        for i in range(start, end):
            if n == string[i]:
                return i

def get_max(string, start, end):
    num = "9876543210"
    for n in num:
        for i in range(start, end):
            if n == string[i]:
                return i

def solution(number, k):
    idx = 0
    while (k > 0):
        if (idx == len(number)-k):
            number = number[:-k]
            break

        max_idx = get_max(number, idx, idx+k+1)

        while (k > 0) and (idx != max_idx):
            min_idx = get_min(number, idx, max_idx)
            number = remove(number, min_idx) # min index로 지우기
            k -= 1
            max_idx -= 1

        idx = max_idx+1

    return number
'''

# fixed
def solution(number, k):
    stack = []
    
    for n in number:
        while (stack) and (stack[-1] < n) and (k > 0):
            stack.pop()
            k -= 1
        stack.append(n)
    
    if k != 0:
        return number[:-k]

    return ''.join(stack)