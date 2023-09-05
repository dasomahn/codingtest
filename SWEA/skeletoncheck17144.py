'''
내 스켈레톤에
빠른 diffusion, clean 넣기
'''

class Room:
    def __init__(self):
        self.r, self.c, self.t = map(int, input().split())
        self.grid = [list(map(int, input().split())) for _ in range(self.r)]

        for r in range(self.r):
            if self.grid[r][0] == -1:
                self.up, self.down = r, r + 1
                break

    def bound(self, x, y):
        if (0 <= x < self.r) and (0 <= y < self.c):
            if (x, y) not in [(self.up, 0), (self.down, 0)]:
                return True
        return False

    def ans_diffusion(self):  # 1초마다 미세먼지가 퍼지는 동작
        change = [[0] * self.c for _ in range(self.r)]
        for x in range(self.r):
            for y in range(self.c):
                if self.grid[x][y] > 0:  # 미세먼지가 있는 경우
                    tmp = 0
                    for i in range(4):  # 4방면으로 퍼짐
                        ax = x + dirs[i][0]
                        ay = y + dirs[i][1]

                        if self.bound(ax, ay):
                            change[ax][ay] += self.grid[x][y] // 5
                            tmp += self.grid[x][y] // 5
                    self.grid[x][y] -= tmp

        for x in range(self.r):
            for y in range(self.c):
                self.grid[x][y] += change[x][y]

    def diffusion(self):
        dust = [[0] * self.c for _ in range(self.r)]

        for x in range(self.r):
            for y in range(self.c):
                div = self.grid[x][y] // 5
                if div > 0:
                    for dx, dy in dirs:
                        nx, ny = x + dx, y + dy
                        if self.bound(nx, ny):
                            dust[nx][ny] += div
                            self.grid[x][y] -= div

        for x in range(self.r):
            for y in range(self.c):
                self.grid[x][y] += dust[x][y]

    def clean(self, direction, x, y):
        if x == self.up:
            edge = 0
        elif x == self.down:
            edge = self.r - 1
        edges = [(x, 0), (x, self.c - 1), (edge, 0), (edge, self.c - 1)]

        for dx, dy in direction:
            while True:
                nx, ny = x + dx, y + dy
                self.grid[x][y] = self.grid[nx][ny]
                x, y = nx, ny

                if (nx, ny) in edges:
                    break

    def ans_clean(self):
        def top_rotate():  # 위쪽 회전
            d = 1  # 오른쪽 방향으로 시작
            before = 0
            x, y = self.up, 1  # 공기청정기 머리부분의 바로 오른쪽 칸부터 시작
            while True:
                ax = x + dx[d]
                ay = y + dy[d]
                if ax == self.r or ay == self.c or ax == -1 or ay == -1:  # 현재 좌표가 꼭짓점인 경우
                    d = (d - 1) % 4
                    continue
                if x == self.up and y == 0:  # 한 바퀴 회전 완료해서 공기청정기 좌표로 다시 돌아온 경우
                    break
                self.grid[x][y], before = before, self.grid[x][y]
                x, y = ax, ay

        def bottom_rotate():  # 아래 회전
            d = 1  # 오른쪽 방향으로 시작
            before = 0
            x, y = self.down, 1  # 공기청정기 아래부분의 바로 오른쪽 칸부터 시작
            while True:
                ax = x + dx[d]
                ay = y + dy[d]
                if ax == self.r or ay == self.c or ax == -1 or ay == -1:  # 현재 좌표가 꼭짓점인 경우
                    d = (d + 1) % 4
                    continue
                if x == self.down and y == 0:  # 한 바퀴 회전 완료해서 공기청정기 좌표로 다시 돌아온 경우
                    break
                self.grid[x][y], before = before, self.grid[x][y]
                x, y = ax, ay

        top_rotate()
        bottom_rotate()

    def monitor(self):
        for _ in range(self.t):
            self.ans_diffusion()

            # self.ans_clean()
            self.clean(dirs, self.up, 0)
            self.clean(c_dirs, self.down, 0)

            self.grid[self.up][0] = 0
            self.grid[self.up][1] = 0
            self.grid[self.down][0] = 0
            self.grid[self.down][1] = 0

        total = sum(sum(self.grid[r]) for r in range(self.r))
        return total

dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

dirs = ((-1, 0), (0, 1), (1, 0), (0, -1))
c_dirs = ((1, 0), (0, 1), (-1, 0), (0, -1))

room = Room()
print(room.monitor())
