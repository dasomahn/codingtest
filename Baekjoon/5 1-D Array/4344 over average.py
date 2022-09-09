casenum = int(input())
res = []

for i in range(casenum):
    case = list(map(int, input().split(" ")))
    num = case[0]
    avg = sum(case[1:])/num

    cnt = 0
    for n in case[1:]:
        if n > avg:
            cnt += 1

    res.append(cnt/num*100)

for r in res: print("{:.3f}%".format(r))