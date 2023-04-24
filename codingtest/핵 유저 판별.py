event_dic = {}

def solution(logs, events):
    for i, event in enumerate(events):
        event_dic[event] = i+1 # 숫자로 편하게 이벤트 순서 매칭

    users = {} # 유저 상태 저장 (직전 이벤트 or -1)
    banned = [] # 불법 사용자 목록

    for log in logs:
        _, user, e = log.split()
        cur = users.get(user, 0) # 유저의 현재 상태 갖고오기

        # 1. 이미 불법 사용자
        if cur == -1: 
            continue
        # 2. 정상 사용자
        elif cur+1 == event_dic[e]:
            users[user] = event_dic[e]
        # 3. 불법 사용 캐치, 등록
        else:
            users[user] = -1
            banned.append(user)

    return ["-1"] if not banned else sorted(banned)