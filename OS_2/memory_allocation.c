#include <stdio.h>
#include <string.h>

#define MAX_PARTITIONS 5
#define MAX_PROCESSES 4

struct Process {
    int id;
    int size;
    int allocated_partition; // -1 if unallocated
    int internal_frag;
};

struct Partition {
    int size;
    int original_size;
    int allocated; // 0 if free, 1 if allocated
};

// 1. First Fit Algorithm
void first_fit(struct Process procs[], int p_n, struct Partition parts[], int p_part_n) {
    // Reset partitions
    for (int i = 0; i < p_part_n; i++) {
        parts[i].size = parts[i].original_size;
        parts[i].allocated = 0;
    }
    for (int i = 0; i < p_n; i++) {
        procs[i].allocated_partition = -1;
        procs[i].internal_frag = 0;
    }

    for (int i = 0; i < p_n; i++) {
        for (int j = 0; j < p_part_n; j++) {
            if (!parts[j].allocated && parts[j].size >= procs[i].size) {
                parts[j].allocated = 1;
                procs[i].allocated_partition = j;
                procs[i].internal_frag = parts[j].size - procs[i].size;
                break; // First fit found, stop searching
            }
        }
    }
}

// 2. Best Fit Algorithm
void best_fit(struct Process procs[], int p_n, struct Partition parts[], int p_part_n) {
    for (int i = 0; i < p_part_n; i++) {
        parts[i].size = parts[i].original_size;
        parts[i].allocated = 0;
    }
    for (int i = 0; i < p_n; i++) {
        procs[i].allocated_partition = -1;
        procs[i].internal_frag = 0;
    }

    for (int i = 0; i < p_n; i++) {
        int best_idx = -1;
        int min_frag = 99999;

        for (int j = 0; j < p_part_n; j++) {
            if (!parts[j].allocated && parts[j].size >= procs[i].size) {
                int frag = parts[j].size - procs[i].size;
                if (frag < min_frag) {
                    min_frag = frag;
                    best_idx = j;
                }
            }
        }

        if (best_idx != -1) {
            parts[best_idx].allocated = 1;
            procs[i].allocated_partition = best_idx;
            procs[i].internal_frag = min_frag;
        }
    }
}

// 3. Worst Fit Algorithm
void worst_fit(struct Process procs[], int p_n, struct Partition parts[], int p_part_n) {
    for (int i = 0; i < p_part_n; i++) {
        parts[i].size = parts[i].original_size;
        parts[i].allocated = 0;
    }
    for (int i = 0; i < p_n; i++) {
        procs[i].allocated_partition = -1;
        procs[i].internal_frag = 0;
    }

    for (int i = 0; i < p_n; i++) {
        int worst_idx = -1;
        int max_size = -1;

        for (int j = 0; j < p_part_n; j++) {
            if (!parts[j].allocated && parts[j].size >= procs[i].size) {
                if (parts[j].size > max_size) {
                    max_size = parts[j].size;
                    worst_idx = j;
                }
            }
        }

        if (worst_idx != -1) {
            parts[worst_idx].allocated = 1;
            procs[i].allocated_partition = worst_idx;
            procs[i].internal_frag = parts[worst_idx].size - procs[i].size;
        }
    }
}

// Display Results Function
void display_results(const char *strategy_name, struct Process procs[], int p_n, struct Partition parts[]) {
    printf("\n--- %s Strategy ---\n", strategy_name);
    printf("Process\tSize\tAllocated Partition (KB)\tInternal Fragmentation (KB)\n");
    
    int total_frag = 0;
    int unallocated_count = 0;

    for (int i = 0; i < p_n; i++) {
        if (procs[i].allocated_partition != -1) {
            int part_size = parts[procs[i].allocated_partition].original_size;
            printf("P%d\t%dKB\tPartition of %dKB\t\t%dKB\n", 
                   procs[i].id, procs[i].size, part_size, procs[i].internal_frag);
            total_frag += procs[i].internal_frag;
        } else {
            printf("P%d\t%dKB\tUNALLOCATED\t\t\t-\n", procs[i].id, procs[i].size);
            unallocated_count++;
        }
    }

    printf("Total Internal Fragmentation: %dKB\n", total_frag);
    if (unallocated_count > 0) {
        printf("Unallocated Processes: ");
        for (int i = 0; i < p_n; i++) {
            if (procs[i].allocated_partition == -1) {
                printf("P%d ", procs[i].id);
            }
        }
        printf("\n");
    } else {
        printf("Unallocated Processes: None\n");
    }
}

int main() {
    // Initializing Partitions: 100, 500, 200, 300, 600
    struct Partition partitions[MAX_PARTITIONS] = {
        {100, 100, 0}, {500, 500, 0}, {200, 200, 0}, {300, 300, 0}, {600, 600, 0}
    };

    // Initializing Processes: P1=212, P2=417, P3=112, P4=426
    struct Process processes_ff[MAX_PROCESSES] = {{1, 212, -1, 0}, {2, 417, -1, 0}, {3, 112, -1, 0}, {4, 426, -1, 0}};
    struct Process processes_bf[MAX_PROCESSES] = {{1, 212, -1, 0}, {2, 417, -1, 0}, {3, 112, -1, 0}, {4, 426, -1, 0}};
    struct Process processes_wf[MAX_PROCESSES] = {{1, 212, -1, 0}, {2, 417, -1, 0}, {3, 112, -1, 0}, {4, 426, -1, 0}};

    first_fit(processes_ff, MAX_PROCESSES, partitions, MAX_PARTITIONS);
    display_results("First Fit", processes_ff, MAX_PROCESSES, partitions);

    best_fit(processes_bf, MAX_PROCESSES, partitions, MAX_PARTITIONS);
    display_results("Best Fit", processes_bf, MAX_PROCESSES, partitions);

    worst_fit(processes_wf, MAX_PROCESSES, partitions, MAX_PARTITIONS);
    display_results("Worst Fit", processes_wf, MAX_PROCESSES, partitions);

    printf("\n=== CONCLUSION ===\n");
    printf("Best Fit is the optimal strategy because it successfully allocates ALL processes\n");
    printf("and achieves the lowest total internal fragmentation (433KB) compared to First Fit and Worst Fit.\n");

    return 0;
}
