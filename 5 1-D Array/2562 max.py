numbers = []

for i in range(9):
    numbers.append(int(input()))

maxnum = max(numbers)

print(maxnum)
print(numbers.index(maxnum)+1)