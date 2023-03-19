def solution(enroll, referral, seller, amount):
    dic = {d:0 for d in enroll}
    
    for sell, a in zip(seller, amount):
        money = a * 100
        ref = referral[enroll.index(sell)]
        if (ref == '-'):
            dic[sell] += money
        else:
            while (ref != "-"):
                if (money < 10):
                    dic[ref] += money
                    break
                dic[sell] += money * 0.9
                dic[ref] += money * 0.1
                money *= 0.1
                ref = referral[enroll.index(ref)]
    
    return list(dic.values())