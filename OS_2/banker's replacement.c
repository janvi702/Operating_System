#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define P 4 // Number of processes (P0 - P3)
#define R 3 // Number of resource types (A, B, C)

// Function to calculate Need matrix
void calculate_need(int need[P][R], int max[P][R], int alloc[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Function to check if the system is in a safe state and populate safe sequence
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
                bool can_allocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int k = 0; k < R; k++) {
                        work[k] += alloc[i][k];
                    }
                    safe_seq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false; // Unsafe state
        }
    }
    return true; // Safe state
}

// Function to handle independent resource requests
void process_request(int p_idx, int request[R], int base_alloc[P][R], int base_max[P][R], int base_avail[R]) {
    int alloc[P][R], max[P][R], need[P][R], avail[R];
    
    // Copy base state
    memcpy(alloc, base_alloc, sizeof(alloc));
    memcpy(max, base_max, sizeof(max));
    memcpy(avail, base_avail, sizeof(avail));
    calculate_need(need, max, alloc);

    printf("\n--------------------------------------------------\n");
    printf("Evaluating Request by P%d for (%d, %d, %d):\n", p_idx, request[0], request[1], request[2]);

    // Step 1: Check if Request <= Need
    for (int j = 0; j < R; j++) {
        if (request[j] > need[p_idx][j]) {
            printf("RESULT: DENIED. Process P%d exceeded its maximum declared need.\n", p_idx);
            return;
        }
    }

    // Step 2: Check if Request <= Available
    for (int j = 0; j < R; j++) {
        if (request[j] > avail[j]) {
            printf("RESULT: DENIED / MUST WAIT. Not enough resources available right now.\n");
            return;
        }
    }

    // Step 3: Pretend to allocate resources
    for (int j = 0; j < R; j++) {
        avail[j] -= request[j];
        alloc[p_idx][j] += request[j];
        need[p_idx][j] -= request[j];
    }

    int safe_seq[P];
    if (is_safe_state(alloc, need, avail, safe_seq)) {
        printf("RESULT: GRANTED! The resulting state is SAFE.\n");
        printf("New Safe Sequence: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", safe_seq[i]);
        }
        printf("\n");
        printf("New Available Resources: (%d, %d, %d)\n", avail[0], avail[1], avail[2]);
    } else {
        printf("RESULT: DENIED. Granting this request leads to an UNSAFE (deadlock-prone) state.\n");
    }
}

int main() {
    // Initial system data
    int alloc[P][R] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 3}, // P2
        {2, 1, 1}  // P3
    };

    int max[P][R] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 6}, // P2
        {2, 2, 2}  // P3
    };

    int avail[R] = {3, 3, 2};
    int need[P][R];

    calculate_need(need, max, alloc);

    // Display Initial State
    printf("=== BANKER'S ALGORITHM (DEADLOCK AVOIDANCE) ===\n\n");
    printf("Process\tAllocation (A B C)\tMax (A B C)\tNeed (A B C)\n");
    for (int i = 0; i < P; i++) {
        printf("P%d\t%d %d %d\t\t%d %d %d\t\t%d %d %d\n", 
               i, alloc[i][0], alloc[i][1], alloc[i][2],
               max[i][0], max[i][1], max[i][2],
               need[i][0], need[i][1], need[i][2]);
    }
    printf("\nInitial Available Resources: A=%d, B=%d, C=%d\n", avail[0], avail[1], avail[2]);

    // Verify initial safe state
    int safe_seq[P];
    if (is_safe_state(alloc, need, avail, safe_seq)) {
        printf("\nVerification: Initial state is SAFE.\n");
        printf("Initial Safe Sequence: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", safe_seq[i]);
        }
        printf("\n");
    } else {
        printf("\nVerification: Initial state is UNSAFE.\n");
    }

    // Process independent requests
    int req_a[R] = {1, 0, 2};
    int req_b[R] = {0, 2, 0};
    int req_c[R] = {4, 0, 1};

    process_request(1, req_a, alloc, max, avail); // (a) P1 requests (1,0,2)
    process_request(0, req_b, alloc, max, avail); // (b) P0 requests (0,2,0)
    process_request(2, req_c, alloc, max, avail); // (c) P2 requests (4,0,1)

    return 0;
}
