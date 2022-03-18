numbers=[]
for i in range(10):
    numbers.append(int(input()))

result = set(map(lambda x: x%42, numbers))
print(len(result))