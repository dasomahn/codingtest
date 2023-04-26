import random
import time

dic = {"L": (-1, 0), "R": (1, 0), "U": (0, 1), "D": (0, -1)}

def solution(commands):
    x, y = 0, 0
    for cmd in commands:
        dx, dy = dic[cmd]
        x, y = x + dx, y + dy
    return [x, y]

def solution2(commands):
    current_position = [0, 0]
    for d in commands:
        if d == "L":
            current_position[0] -= 1
        elif d == "R":
            current_position[0] += 1
        elif d == "U":
            current_position[1] += 1
        elif d == "D":
            current_position[1] -= 1
    return current_position

start_time = time.time()
for i in range(100):
    print(f"try #{i + 1} ", end=" ")
    length = random.randint(1, 100)  # 원소 갯수
    arr = random.choices(["U", "R", "D", "L"], k=length)  # 원소 수

    solution(arr)
end_time = time.time()
print(f"\ntime: {(end_time-start_time)/10:.6f}")

start_time = time.time()
for i in range(100):
    print(f"try #{i + 1} ", end=" ")
    length = random.randint(1, 100)  # 원소 갯수
    arr = random.choices(["U", "R", "D", "L"], k=length)  # 원소 수

    solution2(arr)
end_time = time.time()
print(f"\ntime: {(end_time-start_time)/10:.6f}")
