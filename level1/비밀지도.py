def solution(n, arr1, arr2):
    answer = []
    
    m = [ (arr1[i] | arr2[i]) for i in range(n)]
    
    for row in m:
        binary = str(bin(row))[2:]
        lst = ""
        
        if len(binary)<n:
            print(binary)       
            lst += " "*(n-len(binary))
            
        for i in binary:
            lst += "#" if i == "1" else " "
        answer.append(lst)
    
    return answer

# fixed

def solution(n, arr1, arr2):
    answer = []
    
    # m = [ (arr1[i] | arr2[i]) for i in range(n)]
    # for row in m:
    #     binary = str(bin(row))[2:]
    for i, j in zip(arr1, arr2):
        binary = bin(i|j)[2:]
        
        # if len(binary)<n:
        #     print(binary)       
        #     lst += " "*(n-len(binary))
        binary = binary.rjust(n, "0")
        
        # for i in binary:
        #     lst += "#" if i == "1" else " "
        binary = binary.replace("0", " ")
        binary = binary.replace("1", "#")
            
        answer.append(binary)
    
    return answer
