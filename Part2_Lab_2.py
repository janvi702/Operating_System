# Preemptive Shortest Job First (SRTF)

n = int(input("Enter number of processes: "))

process = []
arrival = []
burst = []

for i in range(n):
    print(f"\nProcess P{i+1}")
    arrival.append(int(input("Arrival Time: ")))
    burst.append(int(input("Burst Time: ")))
    process.append("P" + str(i + 1))

remaining = burst[:]
completion = [0] * n

time = 0
completed = 0
gantt = []

while completed < n:
    idx = -1
    minimum = 9999

    # Find process with shortest remaining time
    for i in range(n):
        if arrival[i] <= time and remaining[i] > 0:
            if remaining[i] < minimum:
                minimum = remaining[i]
                idx = i

    if idx == -1:
        gantt.append("Idle")
        time += 1
        continue

    gantt.append(process[idx])
    remaining[idx] -= 1
    time += 1

    if remaining[idx] == 0:
        completion[idx] = time
        completed += 1

# Calculate TAT and WT
turnaround = []
waiting = []

total_tat = 0
total_wt = 0

for i in range(n):
    tat = completion[i] - arrival[i]
    wt = tat - burst[i]

    turnaround.append(tat)
    waiting.append(wt)

    total_tat += tat
    total_wt += wt

avg_tat = total_tat / n
avg_wt = total_wt / n

# Display Table
print("\nProcess\tAT\tBT\tCT\tTAT\tWT")
for i in range(n):
    print(f"{process[i]}\t{arrival[i]}\t{burst[i]}\t{completion[i]}\t{turnaround[i]}\t{waiting[i]}")

# Display Averages
print("\nAverage Turnaround Time =", round(avg_tat, 2))
print("Average Waiting Time    =", round(avg_wt, 2))

# Display Gantt Chart
print("\nGantt Chart:")
for p in gantt:
    print("|", p, end=" ")
print("|")

print("0", end="")
for i in range(1, len(gantt) + 1):
    print(f" {i}", end="")
print()
