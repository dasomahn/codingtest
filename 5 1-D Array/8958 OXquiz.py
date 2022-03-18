num = int(input())
res = []

for i in range(num):
    case = input()
    split = case.split("X")
    score = 0

    for correct in split:
        succ = len(correct)
        score += succ*(succ+1)/2
    res.append(score)

for r in res: print(int(r))