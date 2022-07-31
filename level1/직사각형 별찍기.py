a, b = map(int, input().strip().split(' '))

# answer = "*"*a
# while(b-1):
#     answer += "\n" + "*"*a
#     b -=1
    
# print(answer)

# print(("*"*a+"\n")*b)

answer = "*"*a
for _ in range(b):
    print(answer)