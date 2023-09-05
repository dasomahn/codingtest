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
sys.stdin = open("17144input.txt", "r")

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

        change = [[0] * self.C for _ in range(self.R)]
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

    def monitor(self):
        for _ in range(self.t):
            self.diffusion()

            self.clean(dirs, self.up, 0)
            self.clean(c_dirs, self.down, 0)

            self.grid[self.up][0] = 0
            self.grid[self.up][1] = 0
            self.grid[self.down][0] = 0
            self.grid[self.down][1] = 0

        total = sum(sum(self.grid[r]) for r in range(self.r))
        return total

dirs = ((-1, 0), (0, 1), (1, 0), (0, -1))
c_dirs = ((1, 0), (0, 1), (-1, 0), (0, -1))



T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    # ///////////////////////////////////////////////////////////////////////////////////
    print(f'#{test_case} start---------------------------------------------------')

    room = Room()
    print(room.monitor())

    print(f'#{test_case} end---------------------------------------------------\n')
    # ///////////////////////////////////////////////////////////////////////////////////
