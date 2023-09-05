# swea 기본 틀

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

import copy
import sys
sys.stdin = open("19236input.txt", "r")

T = int(input())

clock = {1: (-1, 0), 2: (-1, -1), 3: (0, -1), 4: (1, -1),
         5: (1, 0), 6: (1, 1), 7: (0, 1), 8: (-1, 1)}
me = {1: "↑", 2: "↖", 3: "←", 4: "↙",
      5: "↓", 6: "↘", 7: "→", 8: "↗"}


class Ocean:
    def __init__(self):
        self.num = [[0] * 4 for _ in range(4)]
        self.dirs = {}
        self.nums_pos = {}
        self.M = -1

        # set grid
        for x in range(4):
            line = list(map(int, input().split()))
            i = 0
            for y in range(4):
                self.num[x][y] = line[i]
                self.nums_pos[self.num[x][y]] = (x, y)
                i += 1
                self.dirs[self.num[x][y]] = line[i]
                i += 1
        # print(self.dirs)

    def outbound(self, x, y):
        if (0 <= x < 4) and (0 <= y < 4):
            return False
        return True

    def shark_eat(self, x, y):
        n = self.num[x][y]

        self.dirs[n] = -1
        self.nums_pos[n] = (-1, -1)
        self.num[x][y] = -1  # 얘가 중요
        return n

    def fish_move(self):
        for i in range(1, 17):  # ------------------------- 16
            # print(f"{i} : {self.num}")
            # 물고기 번호 i의 위치 갖고오기
            x, y = self.nums_pos[i]
            if x == -1 and y == -1:  # 먹힌 물고기
                # print(f"{i} eaten!")
                continue
            # 물고기 번호 i의 방향 갖고오기
            dx, dy = clock[self.dirs[i]]
            nx, ny = x + dx, y + dy

            # 범위 나갔거나 상어가 있는 위치라면
            cnt = 0
            while (self.outbound(nx, ny) or self.num[nx][ny] == -1) and cnt < 8:
                # print(f"{i}물고기 회전중 ...")
                # 반시계 회전
                self.dirs[i] = self.dirs[i] % 8 + 1
                dx, dy = clock[self.dirs[i]]
                nx, ny = x + dx, y + dy

                # 물고기가 못움직이는 경우 체크를 위해
                cnt += 1
            if cnt == 8:
                continue

            # print(f"{x} {y}에 위치한 {i}물고기 "
            #       f"{nx} {ny}에 위치한 {num[nx][ny]}물고기랑 스위치")
            # 번호별 위치 업데이트
            self.nums_pos[self.num[x][y]] = (nx, ny)
            self.nums_pos[self.num[nx][ny]] = (x, y)
            # 물고기 번호 스위치
            self.num[x][y], self.num[nx][ny] = self.num[nx][ny], self.num[x][y]

    def shark_can_move(self, x, y, ndir):
        self.num[x][y] = 0
        mov = []

        for i in range(1, 4):  # 1, 2, 3
            nx = x + ndir[0] * i
            ny = y + ndir[1] * i
            if not self.outbound(nx, ny) and self.num[nx][ny] > 0:
                # 공간 경계 넘지 않고 물고기가 있는 칸
                # print(f"물고기번호: {self.num[nx][ny]}")
                mov.append((nx, ny))

        return mov

    def dfs(self, x, y, total, depth):
        ndir = clock[self.dirs[self.num[x][y]]]
        # print(f"{depth}) shark 현재 {x} {y}={self.num[x][y]}, 방향은 {ndir}")
        # print(f"{depth}) total은 {total}, 최대는 {self.M}")
        # print(f"{depth}) num배열은 복구돼야 하는데: {self.num}")

        save_num = copy.deepcopy(self.num)
        save_dirs = self.dirs.copy()
        save_nums_pos = self.nums_pos.copy()

        n = self.shark_eat(x, y)
        self.fish_move()

        # print(self.num)

        # 방향검증용 print
        '''
        for r in range(4):
            for c in range(4):
                if self.num[r][c] > 0:
                    print(self.num[r][c], me[self.dirs[self.num[r][c]]], ' ', end="")
        '''

        movable = self.shark_can_move(x, y, ndir)


        if not movable:
            # print(f"\n{depth}) 움직일 수 없음. 기존 max", self.M)
            self.M = max(self.M, total + n)
            # print("max 업데이트", self.M)
            return
        # print(f"{depth}) shark 현재 {x} {y}에서 num은 {self.num}")
        # print(f"{depth}) 갈수있는 {movable}들")
        for nx, ny in movable:
            # print(f"{depth}) {nx} {ny}로 갑니다")
            self.dfs(nx, ny, total + n, depth+1)
            # print(f"{depth}) {nx} {ny} 방문이 끝났고, 복구 후 다음 {movable}로 갈 거임")
        self.num = save_num
        self.dirs = save_dirs
        self.nums_pos = save_nums_pos
        # print(f"복구완료 {self.num}")
        # print(f"{depth}모든 것 탐방 완.")
    def shark(self):
        x, y = 0, 0
        self.dfs(x, y, 0, 0)


# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    # ///////////////////////////////////////////////////////////////////////////////////
    print(f"{test_case} start -------------------------------\n")

    ocean = Ocean()
    # print(ocean.nums_pos)
    ocean.shark()

    print(ocean.M)
    print(f"{test_case} end -------------------------------\n")
    # ///////////////////////////////////////////////////////////////////////////////////
