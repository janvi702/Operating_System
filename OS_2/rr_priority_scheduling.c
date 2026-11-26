#include <stdio.h>

struct Process {
    int id;
    int at; // Arrival Time (all 0 here)
    int bt; // Burst Time
    int priority; // Priority (lower number = higher priority)
    int remaining_bt; // For Round Robin
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
};

// Priority Scheduling (Non-Preemptive)
void calculate_priority(struct Process p[], int n) {
    // Sort processes by priority (ascending: lower number = higher priority)
    // If priorities are equal, sort by arrival time (both 0 here)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j+1].priority) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    float total_wt = 0, total_tat = 0;

    printf("\n--- Priority Scheduling (Non-Preemptive) ---\n");
    printf("Gantt Chart: ");

    for (int i = 0; i < n; i++) {
        printf("| P%d ", p[i].id);
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("|\n");

    // Sort back by ID for neat table display
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].id > p[j+1].id) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    // Print Table
    printf("\nPID\tPriority\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].priority, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

// Round Robin Scheduling (Time Quantum = 3)
void calculate_round_robin(struct Process p[], int n, int tq) {
    int current_time = 0;
    int completed = 0;
    float total_wt = 0, total_tat = 0;

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
    }

    printf("\n--- Round Robin Scheduling (Time Quantum = %d) ---\n", tq);
    printf("Gantt Chart: ");

    while (completed < n) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (p[i].remaining_bt > 0) {
                done = 0; // There is still a process to finish

                printf("| P%d ", p[i].id);

                if (p[i].remaining_bt > tq) {
                    current_time += tq;
                    p[i].remaining_bt -= tq;
                } else {
                    current_time += p[i].remaining_bt;
                    p[i].ct = current_time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    p[i].remaining_bt = 0;
                    completed++;

                    total_wt += p[i].wt;
                    total_tat += p[i].tat;
                }
            }
        }

        if (done == 1) break;
    }
    printf("|\n");

    // Sort back by ID for neat table display
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].id > p[j+1].id) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    // Print Table
    printf("\nPID\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    // Process Initialization: P1, P2, P3, P4, P5 (All arrive at AT = 0)
    struct Process p_priority[5] = {
        {1, 0, 10, 3, 10, 0, 0, 0},
        {2, 1, 1, 1, 1, 0, 0, 0},
        {3, 2, 2, 4, 2, 0, 0, 0},
        {4, 3, 1, 5, 1, 0, 0, 0},
        {5, 4, 5, 2, 5, 0, 0, 0}
    };
    // Reset arrival times to 0 explicitly for safety
    for(int i=0; i<5; i++) p_priority[i].at = 0;

    struct Process p_rr[5] = {
        {1, 0, 10, 3, 10, 0, 0, 0},
        {2, 0, 1, 1, 1, 0, 0, 0},
        {3, 0, 2, 4, 2, 0, 0, 0},
        {4, 0, 1, 5, 1, 0, 0, 0},
        {5, 0, 5, 2, 5, 0, 0, 0}
    };

    calculate_priority(p_priority, 5);
    calculate_round_robin(p_rr, 5, 3);

    printf("\n=== CONCLUSION ===\n");
    printf("Round Robin is more optimal for this specific set of processes because it yields a lower\n");
    printf("average waiting time (6.40 vs 8.20) and lower average turnaround time (10.20 vs 12.00).\n");

    return 0;
}
