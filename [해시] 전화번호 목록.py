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
    #         if phone_book[i][0] == phone_book[j][0]:
    #             if phone_book[j].startswith(phone_book[i]):
    #                 return False
    # return True
    
    phone_book.sort()
    length = len(phone_book)
    
    for i in range(length-1):
        if phone_book[i+1].startswith(phone_book[i]):
            return False
    
    return True