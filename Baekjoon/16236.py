from collections import deque

class Ocean:
    def __init__(self, N):
        self.N = N

        self.exp = 0
        self.lv = 2
        self.time = 0

        self.grid = None
        # self.sx = -1 # shark pos
        # self.sy = -1 # shark pos

    def set(self):
        grid = []
        for r in range(N):
            row = list(map(int, input().split(" ")))
            for c in range(N):
                if row[c] == 9:
                    self.sx, self.sy = r, c
            grid.append(row)
        self.grid = grid

    def eat(self, x, y, dist):
        self.sx, self.sy = x, y
        self.time += dist
        self.exp += 1
        if self.exp == self.lv:
            self.lv += 1
            self.exp = 0

    def check(self, nx, ny):
        if (0 <= nx < self.N and 0 <= ny < self.N) and \
                self.grid[nx][ny] <= self.lv:
            return True
        return False

    def search(self):
        visited = [[0] * self.N for _ in range(self.N)]
        min_dist = 401

        x, y, dist = self.sx, self.sy, 0
        visited[x][y] = 1

        result = []
        queue = deque([((x, y), dist)])
        while (queue):
            (x, y), dist = queue.popleft()

            if dist > min_dist:
                break

            if self.grid[x][y] and self.grid[x][y] < self.lv:
                result.append((x, y))
                min_dist = dist

            for dx, dy in dirs:
                nx, ny = x + dx, y + dy

                if self.check(nx, ny) and not visited[nx][ny]:
                    queue.append(((nx, ny), dist + 1))
                    visited[nx][ny] = 1

        return result, min_dist

    def play(self):
        while True:
            self.grid[self.sx][self.sy] = 0
            res, dist = self.search()
            if not res:
                break

            res.sort(key=lambda x: (x[0], x[1]))
            self.eat(res[0][0], res[0][1], dist)

        return self.time

dirs = ((-1, 0), (0, -1), (0, 1), (1, 0))

N = int(input())
ocean = Ocean(N)
ocean.set()
t = ocean.play()

print(t)
