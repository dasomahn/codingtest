import time

def bound(x, y, n):
	if 0<=x<n and 0<=y<n:
		return True
	return False

def solution(n):	
	grid = [[0] * n for _ in range(n)]
	
	# 우, 하, 좌, 상 순
	dx = (0, 1, 0, -1)
	dy = (1, 0, -1, 0)
	
	d = 0
	x, y = 0, -1
	for i in range(1, n*n+1):
		nx, ny = x+dx[d], y+dy[d]
		if not bound(nx, ny, n) or grid[nx][ny]:
			d = (d+1)%4
			nx, ny = x+dx[d], y+dy[d]
		grid[nx][ny] = i
		x, y = nx, ny
	
	return sum([grid[i][i] for i in range(n)])

def solution2(n):
	answer = 0

	start = 1
	while n > 0:
		if n == 1:
			answer += start
		else:
			answer += start + start + (n - 1) * 2
			start += (n - 1) * 4
		n -= 2

	return answer

start_time = time.time()
for i in range(10):
	print(f"try #{i+1} ", end=" ")
	for n in range(1, 101):
		solution(n)
end_time = time.time()
print(f"\ntime: {(end_time-start_time)/10:.6f}")

start_time = time.time()
for i in range(10):
	print(f"try #{i+1} ", end=" ")
	for n in range(1, 101):
		solution2(n)
end_time = time.time()
print(f"\ntime: {(end_time-start_time)/10:.6f}")
