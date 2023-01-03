import heapq

def solution(jobs): # jobs = (req time, run time)
    total, time = 0, 0
    cnt = len(jobs)

    heapq.heapify(jobs) # 요청순 정렬
    queue = []
    
    while(jobs or queue):
        while (jobs and jobs[0][0] <= time):
            req, task = heapq.heappop(jobs)
            heapq.heappush(queue, [task, req])
        
        if (queue):
            task, req = heapq.heappop(queue)
            total += task + time - req
            time += task
        else:
            time += 1
        
    return (total // cnt)