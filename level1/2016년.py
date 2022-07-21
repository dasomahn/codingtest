def solution(a, b):
    day = ['THU', 'FRI', 'SAT', 'SUN', 'MON', 'TUE', 'WED']
    total = b
    
    for i in range(1, a):
        if i == 2:
            total += 29
        elif i in [1, 3, 5, 7, 8, 10, 12]:
            total += 31
        else:
            total += 30    
    
    return day[total%7]

# simpler code
    date = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    
    return day[(sum(date[:a-1]) + b)%7]