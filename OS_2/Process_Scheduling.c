#include <stdio.h>

struct Process {
    int id;
    int at; // Arrival Time
    int bt; // Burst Time
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
    int completed;
};

void calculate_fcfs(struct Process p[], int n) {
    // Sort processes by Arrival Time (for FCFS)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j+1].at) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    float total_wt = 0, total_tat = 0;

    printf("\n--- FCFS Scheduling Algorithm ---\n");
    printf("Gantt Chart: ");

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) {
            current_time = p[i].at; // CPU is idle until process arrives
        }
        printf("| P%d ", p[i].id);
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("|\n");

    // Print Table
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

void calculate_sjf(struct Process p[], int n) {
    int current_time = 0;
    int completed_count = 0;
    float total_wt = 0, total_tat = 0;

    // Reset completion status
    for (int i = 0; i < n; i++) {
        p[i].completed = 0;
    }

    printf("\n--- SJF (Non-Preemptive) Scheduling Algorithm ---\n");
    printf("Gantt Chart: ");

    int execution_order[10], order_idx = 0;

    while (completed_count < n) {
        int idx = -1;
        int min_bt = 9999;

        // Find the process with minimum burst time among arrived & incomplete processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].completed) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU is idle, jump time to next arriving process
            current_time++;
        } else {
            printf("| P%d ", p[idx].id);
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            completed_count++;
        }
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
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    // Initializing the processes: P1, P2, P3, P4, P5
    struct Process p_fcfs[5] = {
        {1, 0, 6, 0, 0, 0, 0},
        {2, 1, 8, 0, 0, 0, 0},
        {3, 2, 7, 0, 0, 0, 0},
        {4, 3, 3, 0, 0, 0, 0},
        {5, 4, 4, 0, 0, 0, 0}
    };

    struct Process p_sjf[5] = {
        {1, 0, 6, 0, 0, 0, 0},
        {2, 1, 8, 0, 0, 0, 0},
        {3, 2, 7, 0, 0, 0, 0},
        {4, 3, 3, 0, 0, 0, 0},
        {5, 4, 4, 0, 0, 0, 0}
    };

    calculate_fcfs(p_fcfs, 5);
    calculate_sjf(p_sjf, 5);

    printf("\n=== CONCLUSION ===\n");
    printf("SJF is the optimal schedule because it yields a lower average waiting time (7.60 vs 11.00)\n");
    printf("and lower average turnaround time (13.20 vs 16.60) compared to FCFS.\n");

    return 0;
}
