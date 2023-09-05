import copy
import sys
sys.stdin = open("19236input.txt", "r")

def outbound(x, y):
    if (0 <= x < 4) and (0 <= y < 4):
        return False
    return True


class Ocean:
    def __init__(self):
        # self.nums_pos = {}
        self.M = -1

        # set grid
        grid = [[], [], [], []]  # [숫자, 방향] 꼴
        for x in range(4):
            line = list(map(int, input().split()))
            for y in range(4):
                grid[x].append([line[2 * y], line[2 * y + 1]])
                # self.nums_pos[grid[x][y][0]] = (x, y)
        self.grid = grid

    def find_fish(self, num):
        for i in range(4):
            for j in range(4):
                if self.grid[i][j][0] == num:
                    return (i, j)

        return (-1, -1)

    def fish_move(self):
        for i in range(1, 17):
            # 물고기 번호 i의 위치 갖고오기
            # x, y = self.nums_pos[i]
            x, y = self.find_fish(i)
            if x == -1 and y == -1:  # 먹힌 물고기
                # print(f"{i} eaten!")
                continue

            # 물고기 번호 i의 방향 갖고오기
            dx, dy = dirs[self.grid[x][y][1]]
            nx, ny = x + dx, y + dy

            # 범위 나갔거나 상어가 있는 위치라면
            cnt = 0
            while (outbound(nx, ny) or self.grid[nx][ny][0] == -1) and cnt < 8:
                # print(f"{i}물고기 회전중 ...")
                # 반시계 회전
                self.grid[x][y][1] = self.grid[x][y][1] % 8 + 1
                dx, dy = dirs[self.grid[x][y][1]]
                nx, ny = x + dx, y + dy

                # 물고기가 못움직이는 경우 체크를 위해
                cnt += 1

            if cnt == 8:
                continue

            # print(f"{x} {y}에 위치한 {i}물고기 "
            #       f"{nx} {ny}에 위치한 {num[nx][ny]}물고기랑 스위치")
            # 번호별 위치 업데이트
            # self.nums_pos[self.grid[x][y][0]] = (nx, ny)
            # self.nums_pos[self.grid[nx][ny][0]] = (x, y)
            # 물고기 스위치
            self.grid[x][y], self.grid[nx][ny] = self.grid[nx][ny], self.grid[x][y]
            # print(f"\t{i}: {self.grid}")

    def shark_can_move(self, x, y, ndir):
        mov = []
        for i in range(1, 4):  # 1, 2, 3
            nx = x + ndir[0] * i
            ny = y + ndir[1] * i
            if not outbound(nx, ny) and self.grid[nx][ny][0] > 0:
                # 공간 경계 넘지 않고 물고기가 있는 칸
                mov.append((nx, ny))

        return mov

    def shark_eat(self, x, y):
        n = self.grid[x][y][0]

        # self.nums_pos[n] = (-1, -1)
        self.grid[x][y][0] = -1  # 얘가 중요
        return n
    def dfs(self, x, y, total):
        num, dirnum = self.grid[x][y]

        n = self.shark_eat(x, y)
        self.fish_move()

        movable = self.shark_can_move(x, y, dirs[dirnum])

        save_grid = copy.deepcopy(self.grid)
        # save_nums_pos = self.nums_pos.copy()

        if not movable:
            self.M = max(self.M, total + n)
            return

        for nx, ny in movable:
            self.grid[x][y][0] = 0
            self.dfs(nx, ny, total + n)

            self.grid = save_grid
            # self.nums_pos = save_nums_pos

dirs = {1: (-1, 0), 2: (-1, -1), 3: (0, -1), 4: (1, -1),
        5: (1, 0), 6: (1, 1), 7: (0, 1), 8: (-1, 1)}

T = int(input())

# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    # ///////////////////////////////////////////////////////////////////////////////////
    print(f"{test_case} start --------------------------------------------------------------\n")

    ocean = Ocean()
    # print(ocean.nums_pos)
    # ocean.shark()
    ocean.dfs(0, 0, 0) # 마지막은 depth. 무시

    print(ocean.M)
    print(f"{test_case} end --------------------------------------------------------------\n")
    # ///////////////////////////////////////////////////////////////////////////////////
