class Room:
    def __init__(self, param):
        self.r = int(param[0])
        self.c = int(param[1])
        self.t = int(param[2])
        self.grid = []

        self.up = -1
        self.down = -1
        self.total = 0

    def set(self):
        for row in range(self.r):
            cols = list(map(int, input().split(" ")))
            if cols[0] == -1:
                if self.up == -1:
                    self.up = row
                else:
                    self.down = row
            self.grid.append(cols)
            self.total += sum(cols)

        self.total += 2
        self.grid[self.up][0] = 0
        self.grid[self.down][0] = 0

    def bound(self, x, y):
        if (0 <= x < self.r) and (0 <= y < self.c):
            if (x, y) not in [(self.up, 0), (self.down, 0)]:
                return True
        return False

    def diffusion(self):
        dust = [[0] * self.c for _ in range(self.r)]

        for x in range(self.r):
            for y in range(self.c):
                div = self.grid[x][y] // 5
                if div <= 0:
                    continue

                for dx, dy in dirs:
                    nx, ny = x + dx, y + dy
                    if self.bound(nx, ny):
                        dust[nx][ny] += div
                        self.grid[x][y] -= div

        for x in range(self.r):
            for y in range(self.c):
                self.grid[x][y] += dust[x][y]

    def cleanup(self):
        w, h = self.c - 1, self.up

        # left
        for x in range(h, 0, -1):
            self.grid[x][0] = self.grid[x - 1][0]

        # upper
        for y in range(w):
            self.grid[0][y] = self.grid[0][y + 1]

        # right
        for x in range(h):
            self.grid[x][w] = self.grid[x + 1][w]

        # lower
        for y in range(w, 1, -1):
            self.grid[h][y] = self.grid[h][y - 1]

    def cleandown(self):
        w, h = self.c - 1, self.down

        # left
        for x in range(h, self.r - 1):
            self.grid[x][0] = self.grid[x + 1][0]

        # lower
        for y in range(w):
            self.grid[self.r - 1][y] = self.grid[self.r - 1][y + 1]

        # right
        for x in range(self.r - 1, h, -1):
            self.grid[x][w] = self.grid[x - 1][w]

        # upper
        for y in range(w, 1, -1):
            self.grid[h][y] = self.grid[h][y - 1]

    def monitor(self):
        self.set()

        for i in range(self.t):
            self.diffusion()

            self.cleanup()
            self.cleandown()

            self.total -= (self.grid[self.up][0] + self.grid[self.down][0])
            self.grid[self.up][0] = 0
            self.grid[self.up][1] = 0
            self.grid[self.down][0] = 0
            self.grid[self.down][1] = 0


dirs = ((1, 0), (0, 1), (-1, 0), (0, -1))

param = input().split(" ")
room = Room(param)
room.monitor()

print(room.total)
