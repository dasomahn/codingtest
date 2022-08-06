def solution(phone_book):
# first try
    # for phone in phone_book:
    #     for cmp in phone_book:
    #         if phone != cmp:
    #             if cmp.startswith(phone):
    #                 return False
    # return True

# second try
    # phone_book.sort()
    # length = len(phone_book)
    # for i in range(length-1):
    #     for j in range(i+1, length):
    #         if phone_book[i] == phone_book[j][:len(phone_book[i])]:
    #             return False
    # return True
    
    phone_book.sort()
    dic = {x:[] for x in range(10)}
    for phone in phone_book:
        dic[int(phone[0])].append(phone)
    
    print(sorted(dic.items(), key = lambda x: len(x[1]), reverse = True))