answer = []
a = int(input())
b = int(input())
c = int(input())

res = a*b*c
tolist = str(res)

for num in range(10): # 0~9
    cnt=0
    for i in tolist:
        if int(i) == num:
            cnt += 1
    answer.append(cnt)

for ans in answer:
    print(ans)