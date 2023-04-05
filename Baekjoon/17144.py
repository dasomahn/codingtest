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
            if not (self.up <= x <= self.down and y == 0):
                return True
        return False

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

    def monitor(self):
        for _ in range(self.t):
            self.diffusion()

            self.clean(dirs, self.up, 0)
            self.clean(c_dirs, self.down, 0)

            self.grid[self.up][0] = -1
            self.grid[self.up][1] = 0
            self.grid[self.down][0] = -1
            self.grid[self.down][1] = 0

        total = sum(sum(self.grid[r]) for r in range(self.r)) + 2
        return total

dirs = ((-1, 0), (0, 1), (1, 0), (0, -1))
c_dirs = ((1, 0), (0, 1), (-1, 0), (0, -1))

room = Room()
print(room.monitor())
