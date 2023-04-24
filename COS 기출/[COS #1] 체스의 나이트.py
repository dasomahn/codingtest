def bound(x, y):
	if 0<=x<8 and 0<=y<8:
		return True
	return False

def solution(pos):
	knight = ((-1, -2), (-2, -1), (-2, 1), (-1, 2),
					 (1, 2), (2, 1), (2, -1), (1, -2))
	
	x = ord(pos[0])-ord('A')
	y = int(pos[1])-1
	
	return sum([1 if bound(x+dx, y+dy) else 0 for dx, dy in knight])