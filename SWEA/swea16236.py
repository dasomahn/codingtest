# 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
# 아래 표준 입출력 예제 필요시 참고하세요.

# 표준 입력 예제
'''
a = int(input())                        정수형 변수 1개 입력 받는 예제
b, c = map(int, input().split())        정수형 변수 2개 입력 받는 예제
d = float(input())                      실수형 변수 1개 입력 받는 예제
e, f, g = map(float, input().split())   실수형 변수 3개 입력 받는 예제
h = input()                             문자열 변수 1개 입력 받는 예제
'''

# 표준 출력 예제
'''
a, b = 6, 3
c, d, e = 1.0, 2.5, 3.4
f = "ABC"
print(a)                                정수형 변수 1개 출력하는 예제
print(b, end = " ")                     줄바꿈 하지 않고 정수형 변수와 공백을 출력하는 예제
print(c, d, e)                          실수형 변수 3개 출력하는 예제
print(f)                                문자열 1개 출력하는 예제
'''

'''
      아래의 구문은 input.txt 를 read only 형식으로 연 후,
      앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
      여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
      아래 구문을 이용하면 이후 입력을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.

      따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 구문을 사용하셔도 좋습니다.
      아래 구문을 사용하기 위해서는 import sys가 필요합니다.

      단, 채점을 위해 코드를 제출하실 때에는 반드시 아래 구문을 지우거나 주석 처리 하셔야 합니다.
'''
import sys
from collections import deque

sys.stdin = open("16236input.txt", "r")

T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.

# 왼, 위, 오, 아
dirs = ((-1, 0), (0, -1), (0, 1), (1, 0))


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

    def levelup(self):
        self.exp += 1
        if self.exp == self.lv:
            self.lv += 1
            self.exp = 0

    def check(self, nx, ny):
        if (0 <= nx < self.N and 0 <= ny < self.N) and \
                self.grid[nx][ny] <= self.lv:
            return True
        return False

    def dfs(self, x, y, dist, visited):
        # print(x, y, dist)
        visited[x][y] = 1

        if self.grid[x][y] and self.grid[x][y] < self.lv:
            self.grid[x][y] = 0
            self.sx, self.sy = x, y
            self.time += dist
            print(f'shark eats {self.sx} {self.sy}, dist {dist} cum {self.time}')
            return True

        for dx, dy in dirs:
            nx, ny = x + dx, y + dy
            # print(nx, ny)

            if self.check(nx, ny) and not visited[nx][ny]:
                # print("visit ", nx, ny)
                if self.dfs(nx, ny, dist + 1, visited):
                    return True

        return False

    def search(self):
        # dfs version
        '''
        visited = [[0] * self.N for _ in range(self.N)]
        x, y, dist = self.sx, self.sy, 0
        visited[x][y] = 1

        print(f'find fish! shark at {x}, {y}')
        return self.dfs(x, y, dist, visited)
        '''

        # bfs version
        visited = [[0] * self.N for _ in range(self.N)]
        min_dist = 401

        x, y, dist = self.sx, self.sy, 0
        visited[x][y] = 1

        result = []
        queue = deque([((x, y), dist)])
        while (queue):
            ((x, y), dist) = queue.popleft()
            # print(x, y, dist, queue)

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
        self.grid[self.sx][self.sy] = 0

        while True:
            res, dist = self.search()
            if not res:
                break

            res.sort(key=lambda x: (x[0], x[1]))
            x, y = res[0][0], res[0][1]
            self.grid[x][y] = 0
            self.sx, self.sy = x, y
            self.time += dist
            self.levelup()
            # print("eat", x, y, "time ", self.time)
            # print(f'shark {self.lv} {self.exp}/{self.lv}\n')

        return self.time


for test_case in range(1, T + 1):
    print("\ntest ", test_case, "--------------------------------------------------------")
    # ///////////////////////////////////////////////////////////////////////////////////

    N = int(input())
    ocean = Ocean(N)
    ocean.set()
    # print(ocean.sx, ocean.sy)

    t = ocean.play()
    print(t)

    # ///////////////////////////////////////////////////////////////////////////////////
    print("end of test ", test_case, "--------------------------------------------------------")