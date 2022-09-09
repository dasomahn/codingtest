num = int(input())
scores = list(map(int, input().split(" ")))

maxnum = max(scores)
scores = list(map(lambda x: x/maxnum*100, scores))

print(sum(scores)/len(scores))