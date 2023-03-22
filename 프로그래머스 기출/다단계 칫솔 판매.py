def solution(enroll, referral, seller, amount):
    dic = {d : 0 for d in enroll}
    ref_dic = {r : referral[i] for i, r in enumerate(enroll)}
    
    for sell, a in zip(seller, amount):
        dic[sell] += a * 100 * 0.9
        
        money = a * 100 * 0.1
        ref = ref_dic[sell]
     
        while (ref != "-"):
            dic[ref] += money
            if (money < 10):
                break
            money = int(money * 0.1)
            dic[ref] -= money
            
            ref = ref_dic[ref]

    return list(dic.values())