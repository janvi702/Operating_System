#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resource types

// Function to calculate Need matrix
void calculate_need(int need[P][R], int max[P][R], int alloc[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool is_safe_state(int alloc[P][R], int need[P][R], int avail[R], int safe_seq[P]) {
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    bool finish[P] = {false};
    int count = 0;

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                // Check if need of process i <= work
                bool can_allocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    // If yes, simulate finishing the process
                    for (int k = 0; k < R; k++) {
                        work[k] += alloc[i][k];
                    }
                    safe_seq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process could be allocated in this round, system is unsafe
        if (!found) {
            return false;
        }
    }
    return true;
}

// Function to handle resource request
void request_resources(int p_idx, int request[R], int alloc[P][R], int need[P][R], int avail[R]) {
    // Step 1: Check if request <= need
    for (int i = 0; i < R; i++) {
        if (request[i] > need[p_idx][i]) {
            printf("\nError: Process P%d has exceeded its maximum claim.\n", p_idx);
            return;
        }
    }

    // Step 2: Check if request <= available
    for (int i = 0; i < R; i++) {
        if (request[i] > avail[i]) {
            printf("\nProcess P%d must wait. Resources are not available.\n", p_idx);
            return;
        }
    }

    // Step 3: Pretend to allocate resources
    int avail_backup[R];
    int alloc_backup[P][R];
    int need_backup[P][R];

    for (int i = 0; i < R; i++) avail_backup[i] = avail[i];
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            alloc_backup[i][j] = alloc[i][j];
            need_backup[i][j] = need[i][j];
        }
    }

    // Apply temporary allocation
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        alloc[p_idx][i] += request[i];
        need[p_idx][i] -= request[i];
    }

    int safe_seq[P];
    if (is_safe_state(alloc, need, avail, safe_seq)) {
        printf("\nRESULT: Request by P1 for (1, 0, 2) can be GRANTED immediately!\n");
        printf("New Safe Sequence: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", safe_seq[i]);
        }
        printf("\n");
    } else {
        printf("\nRESULT: Request cannot be granted. It leads to an unsafe state.\n");
        // Rollback state
        for (int i = 0; i < R; i++) avail[i] = avail_backup[i];
        for (int i = 0; i < P; i++) {
            for (int j = 0; j < R; j++) {
                alloc[i][j] = alloc_backup[i][j];
                need[i][j] = need_backup[i][j];
            }
        }
    }
}

int main() {
    // Initialization of matrices
    int alloc[P][R] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    int max[P][R] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    int avail[R] = {3, 3, 2};
    int need[P][R];

    // Calculate Need Matrix
    calculate_need(need, max, alloc);

    // Display Matrices
    printf("=== BANKER'S ALGORITHM SIMULATION ===\n\n");
    printf("Process\tAllocation (A B C)\tMax (A B C)\tNeed (A B C)\n");
    for (int i = 0; i < P; i++) {
        printf("P%d\t%d %d %d\t\t%d %d %d\t\t%d %d %d\n", 
               i, alloc[i][0], alloc[i][1], alloc[i][2],
               max[i][0], max[i][1], max[i][2],
               need[i][0], need[i][1], need[i][2]);
    }

    printf("\nAvailable Resources: A=%d, B=%d, C=%d\n", avail[0], avail[1], avail[2]);

    // Check initial safe state
    int safe_seq[P];
    if (is_safe_state(alloc, need, avail, safe_seq)) {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", safe_seq[i]);
        }
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state.\n");
    }

    // Test request by P1 for (1, 0, 2)
    int p1_request[R] = {1, 0, 2};
    printf("\n--- Simulating Request by P1 for (1, 0, 2) ---");
    request_resources(1, p1_request, alloc, need, avail);

    return 0;
}
