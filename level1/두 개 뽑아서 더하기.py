# from itertools import combinations

def solution(numbers):
    # return sorted( set( sum(i) for i in combinations(numbers, 2) ) )
    answer = []
    for i in range(len(numbers)):
        for j in range(i+1, len(numbers)):
            answer.append(numbers[i]+numbers[j])

    return sorted(set(answer))