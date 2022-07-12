def dist(cur, num):
    dist = 0
    cur = cur if cur != 0 else 11
    num = num if num != 0 else 11

    ab = abs(cur-num)

    if (ab%3) == 0:
        dist = ab/3
    else:
        if ab == 1: 
            dist = 1
        elif ab in [2, 4]:
            dist = 2
        elif ab in [5, 7]:
            dist = 3
        else:
            dist = 4

    return dist

def solution(numbers, hand):
    answer = ''
    left = 10
    right = 12

    for num in numbers:
        if num in [1, 4, 7]:
            answer += "L"
            left = num
        elif num in [3, 6, 9]:
            answer += "R"
            right = num
        else:
            rightdist = dist(right, num)
            leftdist = dist(left, num)

            print(num)
            print(left, right)
            print(leftdist, rightdist)
            if rightdist > leftdist:
                answer += "L"
                left = num
            elif rightdist < leftdist:
                answer += "R"
                right = num
            else:
                if hand == "right":
                    answer += "R"
                    right = num
                else:
                    answer += "L"
                    left = num

    return answer