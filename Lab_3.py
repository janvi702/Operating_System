from collections import deque

class Process: 
    def __init__(self, pid, arrival_time, burst_time): 
        self.pid = pid 
        self.arrival_time = arrival_time 
        self.burst_time = burst_time 
        self.remaining_time = burst_time 
        self.completion_time = 0 
        self.turnaround_time = 0 
        self.waiting_time = 0 

def round_robin_scheduling(processes, quantum): 
    # Sort processes by arrival time
    processes.sort(key=lambda x: x.arrival_time) 
    ready_queue = deque() 
    current_time = 0 
    completed = 0 
    n = len(processes) 
    in_queue = [False] * n 

    # Safely handle start time if first process arrives after time 0
    if processes:
        current_time = processes[0].arrival_time
        for i in range(n):
            if processes[i].arrival_time <= current_time:
                ready_queue.append(i)
                in_queue[i] = True
            else:
                break

    print("\n--- Execution Timeline ---") 

    while completed < n: 
        if not ready_queue: 
            # Handle idle CPU when queue is empty
            next_arrival = min(p.arrival_time for p in processes if p.remaining_time > 0) 
            current_time = max(current_time, next_arrival) 
            for i in range(n): 
                if processes[i].arrival_time <= current_time and not in_queue[i] and processes[i].remaining_time > 0: 
                    ready_queue.append(i) 
                    in_queue[i] = True 

        idx = ready_queue.popleft() 
        p = processes[idx] 

        # Execute for quantum or remaining burst time
        execution_time = min(p.remaining_time, quantum) 
        print(f"Time {current_time:2d}: Process P{p.pid} executes for {execution_time} units.") 

        current_time += execution_time 
        p.remaining_time -= execution_time 

        # Add newly arrived processes to ready queue
        for i in range(n): 
            if processes[i].arrival_time <= current_time and not in_queue[i] and processes[i].remaining_time > 0: 
                ready_queue.append(i) 
                in_queue[i] = True 

        # Re-queue running process if it still has remaining burst time
        if p.remaining_time > 0: 
            ready_queue.append(idx) 
        else: 
            p.completion_time = current_time 
            p.turnaround_time = p.completion_time - p.arrival_time 
            p.waiting_time = p.turnaround_time - p.burst_time 
            completed += 1 

    # Print Results Table
    print("\n" + "="*70) 
    print(f"{'PID':<6}{'Arrival':<10}{'Burst':<8}{'Complete':<10}{'Turnaround':<12}{'Waiting':<8}") 
    print("="*70) 
    total_tat = sum(p.turnaround_time for p in processes) 
    total_wt = sum(p.waiting_time for p in processes) 

    for p in sorted(processes, key=lambda x: x.pid): 
        print(f"P{p.pid:<5}{p.arrival_time:<10}{p.burst_time:<8}{p.completion_time:<10}{p.turnaround_time:<12}{p.waiting_time:<8}") 

    print("="*70) 
    print(f"Average Turnaround Time: {total_tat / n:.2f}") 
    print(f"Average Waiting Time:    {total_wt / n:.2f}\n") 

if __name__ == "__main__": 
    process_list = [
        Process(1, 0, 5), 
        Process(2, 1, 4), 
        Process(3, 2, 2), 
        Process(4, 4, 1)
    ] 
    round_robin_scheduling(process_list, quantum=2)
