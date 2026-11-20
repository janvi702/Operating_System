#include <stdio.h>
#include <stdbool.h>

// Helper function to print current frames
void print_frames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
}

// Function to predict which page to replace (furthest in the future)
int predict(int ref[], int frames[], int ref_len, int frame_count, int current_index) {
    int farthest = current_index;
    int replace_idx = -1;

    for (int i = 0; i < frame_count; i++) {
        int j;
        for (j = current_index + 1; j < ref_len; j++) {
            if (frames[i] == ref[j]) {
                if (j > farthest) {
                    farthest = j;
                    replace_idx = i;
                }
                break;
            }
        }
        // If a page is never used again in the future, it's the best candidate to replace
        if (j == ref_len) {
            return i;
        }
    }

    return (replace_idx != -1) ? replace_idx : 0;
}

// Optimal Page Replacement Simulation
void simulate_optimal(int ref[], int ref_len, int frame_count) {
    int frames[10];
    for (int i = 0; i < frame_count; i++) frames[i] = -1;

    int page_faults = 0;
    int page_hits = 0;

    printf("\n--- Optimal Page Replacement (Frames = %d) ---\n", frame_count);
    printf("Ref\tFrames\t\tStatus\n");

    for (int i = 0; i < ref_len; i++) {
        int page = ref[i];
        bool found = false;

        // Check for Page Hit
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == page) {
                found = true;
                page_hits++;
                break;
            }
        }

        printf("%d\t", page);

        if (!found) {
            // Page Fault
            int empty_slot = -1;
            for (int j = 0; j < frame_count; j++) {
                if (frames[j] == -1) {
                    empty_slot = j;
                    break;
                }
            }

            if (empty_slot != -1) {
                frames[empty_slot] = page;
            } else {
                int replace_idx = predict(ref, frames, ref_len, frame_count, i);
                frames[replace_idx] = page;
            }
            page_faults++;
            print_frames(frames, frame_count);
            printf("\tPage Fault\n");
        } else {
            print_frames(frames, frame_count);
            printf("\tPage Hit\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Total Page Hits: %d\n", page_hits);
    printf("Hit Ratio: %.2f%%\n", ((float)page_hits / ref_len) * 100);
}

int main() {
    int reference_string[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int ref_len = 12;

    // Simulate for 3 Frames
    simulate_optimal(reference_string, ref_len, 3);

    // Simulate for 4 Frames
    simulate_optimal(reference_string, ref_len, 4);

    return 0;
}
