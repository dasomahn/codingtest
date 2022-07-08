# def solution(id_list, report, k):
#     answer = []
    
# #     making dictionary
#     rep_dict = {}
#     res_dict = {}
#     for id in id_list:
#         rep_dict[id] = [0] # reporter dictionary
#         res_dict[id] = 0 # total result email dictionary
    
# #     reporting
#     for case in report:
#         reporter = case.split(" ")[0]
#         rep = case.split(" ")[1]
        
#         if reporter not in rep_dict[rep]:
#             rep_dict[rep][0] += 1
#             rep_dict[rep].append(reporter)

# #     calculating emails
#     for value in list(rep_dict.values()):
#         if value[0] >= k:
#             for reporter in value[1:]:
#                 res_dict[reporter] += 1
    
#     for value in list(res_dict.values()):
#         answer.append(value)
    
#     return answer


# fixed

def solution(id_list, report, k):
    answer = []
    
#     making dictionary
    rep_dict = { x:0 for x in id_list }
    answer = [0]*len(id_list)
    set_report = set(report) 
    
#     reporting
    for case in set_report:
        rep = case.split(" ")[1]
        rep_dict[rep] += 1


#     calculating emails
    for case in set_report:
        if rep_dict[case.split(" ")[1]] >= k:
            answer[id_list.index(case.split(" ")[0])] += 1
    
    return answer