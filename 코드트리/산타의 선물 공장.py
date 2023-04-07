from collections import deque
import sys
sys.stdin = open("산타의 선물 공장input.txt", "r")

# 공장 설립
def init(param):
    global n, m
    # 100 n m ID1 ID2 ... IDn W1 W2 ... Wn 형태로 공백을 사이에 두고 주어집니다.

    # 넘겨오는 건 100 제외
    n, m = param[:2]

    p = n // m
    start = 2
    for beltm in range(1, m + 1):
        # 이는 m개의 벨트와 n개의 선물로 이루어진 공장을 세우며,
        belt_ok[beltm] = 1
        # 선물을 주어진 순서대로 m/n 개씩 잘라 1번 벨트부터 m번 벨트까지 올려줍니다.
        queue = deque()
        for i in range(p):
            queue.append([param[start + i], param[start + i + n]]) # id, weight
            box_pos[param[start + i]] = beltm # belt번호
        belt[beltm] = queue
        start += p


# 물건 하차
def drop(w_max):
    # 산타가 원하는 상자의 최대 무게인 w_max가 주어집니다.
    weight = 0

    # 1번부터 m번까지 순서대로 벨트를 보며
    for beltm in range(1, m + 1):
        # 고장난 벨트 넘어가기
        if not belt_ok[beltm] or not belt[beltm]:
            continue

        # 각 벨트의 맨 앞에 있는 선물 중
        front = belt[beltm].popleft()
        empty = False
        while (box_pos[front[0]] == 0):
            # 혹시 제거되었던 상자가 있다면
            if not belt[beltm]:
                empty = True
                break
            front = belt[beltm].popleft()
        if empty:
            continue

        # 해당 선물의 무게가 w_max 이하라면 하차를 진행하고,
        if front[1] <= w_max:
            weight += front[1]
            box_pos[front[0]] = 0
        # 그렇지 않다면 해당 선물을 벨트 맨 뒤로 보냅니다.
        else:
            belt[beltm].append(front)
        # 벨트에 있던 상자가 빠지면 한 칸씩 앞으로 내려와야 함에 유의합니다.

    return weight


# 물건 제거
def remove(r_id):
    # 산타가 제거하기를 원하는 물건의 고유 번호 r_id가 주어집니다.

    # 번호로 위치 찾기
    try:
        beltnum = box_pos[r_id]
    except KeyError:
        return -1

        # 해당 고유 번호에 해당하는 상자가 놓여있는 벨트가 있다면,
    if beltnum and belt_ok[beltnum]:
                # 해당 벨트에서 상자를 제거하고
                # 이에 따라 뒤에 있던 상자들은 앞으로 한 칸씩 내려오게 됩니다.
        box_pos[r_id] = 0 # 제거 대신 id 0으로 없는 상자 취급

        return r_id

    # 그러한 상자가 있는 경우 r_id값을, 없다면 -1을 출력해야 합니다.
    return -1


# 물건 확인
def find(f_id):
    # 산타가 확인하기를 원하는 물건의 고유 번호 f_id가 주어집니다.

    # 번호로 위치 찾기
    try:
        beltnum = box_pos[f_id]
    except KeyError:
        return -1

            # 해당 고유 번호에 해당하는 상자가 놓여있는 벨트가 있다면,
    if beltnum and belt_ok[beltnum]:
        for idx, box in enumerate(belt[beltnum]):
            if f_id == box[0]:
                # 해당 벨트의 번호를 출력하고,
                belt[beltnum].rotate(-idx)
                # 해당 상자 위에 있는 모든 상자를 전부 앞으로 가져옵니다.
                # 가져올 시 순서는 그대로 유지가 되어야 함에 유의합니다.
                return beltnum

    # 없다면 -1을 출력합니다.
    return -1


# 벨트 고장
def error(b_num):
    # 고장이 발생한 벨트의 번호 b_num이 주어집니다.
    # 이 명령이 주어졌을 때에는 b_num번째 벨트를 제외한 벨트 중 최소 하나 이상이 정상 상태임을 가정해도 좋습니다. 즉, 모든 벨트가 망가지는 경우는 없습니다.

    # 이 명령을 수행하기 전 만약 b_num 벨트가 이미 망가져 있었다면 -1을,
    if not belt_ok[b_num]:
        return -1

    # b_num번째 벨트에 고장이 발생하면 해당 벨트는 다시는 사용할 수 없게 되고,
    belt_ok[b_num] = 0

    # b_num 벨트의 바로 오른쪽 벨트부터 순서대로 보며
    i = b_num + 1
    while (i != b_num):
        if i == m + 1:
            # 만약 m번 벨트까지 봤는데도 고장나지 않은 벨트가 없다면 다시 1번부터 순서대로 벨트를 확인하여,
            i = 1

        # 아직 고장이 나지 않은 최초의 벨트 위로 b_num 벨트에 놓여 있던 상자들을 아래에서부터 순서대로 하나씩 옮겨줍니다.
        if belt_ok[i]:
            belt[i].extend(belt[b_num])

            for bidx, bw in belt[b_num]:
                if box_pos[bidx]:
                    box_pos[bidx] = i

            # 그렇지 않았다면 정상적으로 고장을 처리했다는 뜻으로 b_num 값을 출력합니다.
            return b_num

        i += 1


T = int(input())

# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    print(f"\n{test_case} start ----------------------------------------")

    # 첫 번째 줄에 명령의 수 q가 주어집니다.
    q = int(input())

    belt_ok, belt, box_pos = {}, {}, {}  # 벨트 작동 여부, 벨트 내용, 상자별 벨트
    n, m = 0, 0  # n개 선물, m개 벨트

    # 두 번째 줄부터는 q개의 줄에 걸쳐 명령의 정보가 주어집니다.
    while q:
        line = list(map(int, input().split()))
        cmd = line[0]

        # 각 명령에 따른 형태는 다음과 같습니다.
        if cmd == 100:
            # 공장 설립
            init(line[1:])
        elif cmd == 200:
            # 물건 하차
            print(drop(line[1]))
        elif cmd == 300:
            # 물건 제거
            print(remove(line[1]))
        elif cmd == 400:
            # 물건 확인
            print(find(line[1]))
        elif cmd == 500:
            # 벨트 고장
            print(error(line[1]))

        q -= 1

    print(f"{test_case} end ----------------------------------------\n")