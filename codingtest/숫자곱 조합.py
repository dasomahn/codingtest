def solution(num1, num2):
    num1, num2 = min(num1, num2), max(num1, num2)

    answer = 0
    for a in range(1, num1+1):
        for b in range(1, num2+1):
            abset = set(str(a)+str(b))
            cset = set(str(a*b))

            if abset&cset == cset:
                answer += 1

    return answer