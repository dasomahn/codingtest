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