def solution(absolutes, signs):

    # return sum([x*(1 if y else -1) for x, y in zip(absolutes, signs)])
    return sum([x if y else -x for x, y in zip(absolutes, signs)])