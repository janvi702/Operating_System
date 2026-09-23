# FCFS Scheduling Algorithm

n = int(input("Enter the number of processes: "))

processes = []
burst_time = []

for i in range(n):
    bt = int(input(f"Enter Burst Time for Process P{i+1}: "))
    burst_time.append(bt)

waiting_time = [0] * n
turnaround_time = [0] * n

# Calculate Waiting Time
for i in range(1, n):
    waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1]

# Calculate Turnaround Time
for i in range(n):
    turnaround_time[i] = waiting_time[i] + burst_time[i]

# Calculate Average Waiting Time and Turnaround Time
avg_wt = sum(waiting_time) / n
avg_tat = sum(turnaround_time) / n

# Display Results
print("\nFCFS Scheduling Results")
print("-" * 50)
print("Process\tBurst Time\tWaiting Time\tTurnaround Time")

for i in range(n):
    print(f"P{i+1}\t{burst_time[i]}\t\t{waiting_time[i]}\t\t{turnaround_time[i]}")

print("-" * 50)
print(f"Average Waiting Time    : {avg_wt:.2f}")
print(f"Average Turnaround Time : {avg_tat:.2f}")

# Gantt Chart
print("\nGantt Chart:")
print("0", end="")
current_time = 0
for i in range(n):
    current_time += burst_time[i]
    print(f" --P{i+1}-- {current_time}", end="")
print()