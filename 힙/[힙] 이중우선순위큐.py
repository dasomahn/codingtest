def solution(operations):
    answer = []
    
    for op in operations:
        if op[0] == 'I':
            answer.append(int(op[2:]))
        else:
            if answer:
                if op[2] == '1':
                    answer.remove(max(answer))
                else:
                    answer.remove(min(answer))
    if answer:
        return (max(answer), min(answer))
    else:
        return [0, 0]