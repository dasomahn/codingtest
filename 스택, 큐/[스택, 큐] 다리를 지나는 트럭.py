# def solution(bridge_length, weight, truck_weights):    
#     time = 0
#     bridge_list = []
    
#     while(truck_weights):
#         time += 1
        
#         if len(bridge_list) < bridge_length and sum(i[0] for i in bridge_list) <= weight-truck_weights[0]:
#             bridge_list.append([truck_weights.pop(0), bridge_length])
    
#         for num in range(len(bridge_list)):
#             bridge_list[num][1] -= 1
#         if bridge_list[0][1] == 0:
#             bridge_list.pop(0)
            
#     return time + bridge_list[-1][1] + 1


# fixed
from collections import deque

def solution(bridge_length, weight, truck_weights):    
    time = 0
    # bridge = [0] * bridge_length
    # deque version
    truck_weights = deque(truck_weights)
    bridge = deque([0] * bridge_length)
    bridge_weight = 0
    
    while(truck_weights):
        time += 1
        # bridge_weight -= bridge.pop(0)
        bridge_weight -= bridge.popleft()
        
        if bridge_weight <= weight - truck_weights[0]:
            # truck = truck_weights.pop(0)
            truck = truck_weights.popleft()
            bridge.append(truck)
            bridge_weight += truck
        else:
            bridge.append(0)
            
    return time + bridge_length