def arrivedNow(processes, current_time):
   pros = []
   for p in processes:
      if (p.arrival == current_time):
         pros.append(p)
   return pros

def priorityFirst(pros):
       for p in pros:
              if p.priority not in (1, 2): return False
       return len(pros) > 0

def prioritySecond(pros):
       for p in pros:
              if p.priority not in (3, 4): return False
       return len(pros) > 0

def priorityThird(pros):
       for p in pros:
              if p.priority not in (5, 6): return False
       return len(pros) > 0

def TLQ(processes, quantum=3):
    executed = []
    total_time = 0
    for p in processes:
       total_time += p.burst

    start_time = processes[0].arrival # time initialized to first process arrival time
    turn = 0

    rr_wait_queue = []
    level2_wait_queue = []
    level3_wait_queue = []

    time = start_time
    ps = arrivedNow(processes, start_time)
    if priorityFirst(ps): rr_wait_queue += ps
    if prioritySecond(ps): level2_wait_queue += ps
    if priorityThird(ps): level3_wait_queue += ps
               
    while time < total_time:
        if  (len(rr_wait_queue) > 0):
               p = rr_wait_queue.pop(0) # remove first guy
               count = 0
               while p.burst > 0 and count < quantum:
                      newly_arrived = arrivedNow(processes, time)
                      if len(newly_arrived) > 0:
                             if priorityFirst(newly_arrived): rr_wait_queue += newly_arrived
                             if prioritySecond(newly_arrived): level2_wait_queue += newly_arrived 
                             if priorityThird(newly_arrived): level2_wait_queue += newly_arrived   
                      executed.append(p)
                      time += 1
                      p.burst -= 1
                      count += 1
               if p.burst != 0:
                      rr_wait_queue.append(p) # put back in the wait queue if there is any unfinished business
                      
        elif (len(level2_wait_queue) > 0):
                p = level2_wait_queue.pop(0)
                while p.burst > 0:
                       newly_arrived = arrivedNow(processes, time)
                       if len(newly_arrived) > 0 and priorityFirst(newly_arrived):
                              for arrived_p in newly_arrived:
                                     rr_wait_queue.append(arrived_p)
                                     level2_wait_queue = [p] + level2_wait_queue # has unfinished business, put it back in level 2 queue where it left of
                              break
                       executed.append(p)
                       time += 1
                       p.burst -= 1

    return executed
