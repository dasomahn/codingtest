```
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
```

import re

def solution(dartResult):
    answer = []
    dart = re.findall('(\d+)([SDT])([*#]?)',dartResult)
    # dart = re.findall('\d+[SDT][*#]?',dartResult)
    # without (), results come out as a whole string ex. 3D, not '3', 'D', ''
    
    nums = {'S': 1, 'D': 2, 'T': 3}
    options = {'#': -1, '*': 2, '': 1}
    
    
    for i in range(len(dart)):
        answer.append(int(dart[i][0]) ** nums[dart[i][1]] * options[dart[i][2]])
        
        if i>0 and dart[i][2] == '*':
            answer[i-1] *= 2    
    
    return sum(answer)