'''
def solution(triangle):
    length = len(triangle)
    cases = {}
    
    for i, tri in enumerate(triangle):
        if (i == 0):
            cases[0] = [tri[0]]
            continue
        
        case = []
        length = len(tri)
        upper = cases[i - 1]
        
        for j, num in enumerate(tri):
            if j == 0:
                case.append(num + upper[j])
            elif (j+1 == length):
                case.append(num + upper[j-1])
            else:
                case.append(num + max(upper[j-1], upper[j]))
                
        cases[i] = case
        
    return max(cases[length-1])
'''

# fixed
def solution(triangle):
    length = len(triangle)
    
    for i in range(length-2, -1, -1):
        for j in range(i+1):
            triangle[i][j] += max(triangle[i+1][j], triangle[i+1][j+1])
        
    return triangle[0][0]