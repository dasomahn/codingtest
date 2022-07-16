import re

def solution(dartResult):
    nums = list(map(int, re.findall('\d+', dartResult)))
    options = re.sub('\d','', dartResult)

    i = 0
    j = 0
    while(j < len(options)):
        opt = options[j]        
        j += 1

        if opt.isalpha():
            if opt == "S":
                nums[i] **= 1
            elif opt == "D":
                nums[i] **= 2
            elif opt == "T":
                nums[i] **= 3
            i += 1
            
        else:
            i -= 1
            if opt == "#":
                nums[i] *= -1
            elif opt == "*":
                nums[i] *= 2
                if(i>0):
                    nums[i-1] *= 2
            i += 1

    return sum(nums)