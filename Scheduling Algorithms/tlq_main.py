from TLQ import TLQ

def ganttChart(output):
    t = 1
    gantt = []
    pros  =[]
    for i in xrange(len(output) - 1):
        p = output[i]
        p_next = output [i+1]
        if (p.pid != p_next.pid):
            gantt.append(t)
            pros.append(p)
        t += 1
    gantt.append(len(output))
    pros.append(output[len(output)-1])

    print "\n+" + "-----+" * len(gantt) + "\n|",			
    for element in pros: print str(element.pid).center(4, " ") + "|",	
    print "\n+" + "-----+" * len(gantt) + "\n0",
    for element in gantt: print "%5d" % element,
        

class Process:
   def __init__(self, pid, arrival, burst, priority):
      self.pid = pid
      self.priority = priority
      self.arrival = arrival
      self.burst = burst
      self.finished_time = 0
      self.waiting_time = 0
      self.turnaround_time = 0

p1 = Process(1, 0, 8, 2)
p2 = Process(2, 4, 15, 5)
p3 = Process(3, 7, 9, 3)
p4 = Process(4, 13, 5, 1)
p5 = Process(5, 9, 13, 4)
p6 = Process(6, 0, 6, 1)

processes = [p1, p2, p3, p4, p5, p6]
processes = sorted(processes, key=lambda p : p.arrival)
start_time = processes[0].arrival

level1_rr = [p for p in processes if p.priority in (1, 2)]
level2_fcfs = [p for p in processes if p.priority in (3, 4)]
level3_fcfs = [p for p in processes if p.priority in (5, 6)]

mltq = TLQ(processes, 3)
def setWaitingTimes(output):
    seen = []
    t = 0
    for p in output:
        if not p in seen:
            seen.append(p)
            p.waiting_time = t
        t += 1

def setFinishedTimes(output):
    i = len(output) - 1
    seen = []
    while i >= 0:
        p = output[i]
        if not p in seen:
            seen.append(p)
            p.finished_time = i
        i -= 1

def setTurnaroundTimes(pros):
    for p in pros:
        p.turnaround_time = p.finished_time - p.arrival


# Analyze mltq algorithm output for statistics

processes = sorted(processes, key=lambda p : p.pid)
setWaitingTimes(mltq)
setFinishedTimes(mltq)
setTurnaroundTimes(processes)

ganttChart(mltq)

total_waiting_time = sum(p.waiting_time for p in processes)
numProcesses = float(len(processes))
total_turnaround_time = sum(p.turnaround_time for p in processes)
average_waiting_time = float(total_waiting_time) / numProcesses
average_turnaround_time = float(total_turnaround_time) / numProcesses
print "\n\nTotal waiting time: %d ms" % total_waiting_time
print "Total turnaround time: %d ms" % total_turnaround_time
print "Average waiting time: %.2f ms" % average_waiting_time
print "Average turnaround time: %.2f ms\n" % average_turnaround_time
