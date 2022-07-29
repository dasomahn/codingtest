def solution(num):
    # return "Odd" if num%2 else "Even" 
    return ["Even", "Odd"][num & 1]