#include <stdio.h>
#include <stdbool.h>

#define MAX_REF 20
#define MAX_FRAMES 3

// Helper function to print current frames
void print_frames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
}

// FIFO Page Replacement Simulation
void simulate_fifo(int ref[], int ref_len, int frame_count) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < frame_count; i++) frames[i] = -1;

    int page_faults = 0;
    int page_hits = 0;
    int fifo_index = 0; // Points to the oldest page

    printf("\n--- FIFO Page Replacement Simulation ---\n");
    printf("Ref\tFrames\t\tStatus\n");

    for (int i = 0; i < ref_len; i++) {
        int page = ref[i];
        bool found = false;

        // Check if page is already in frames (Hit)
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == page) {
                found = true;
                page_hits++;
                break;
            }
        }

        printf("%d\t", page);

        if (!found) {
            // Page Fault: Replace oldest page
            frames[fifo_index] = page;
            fifo_index = (fifo_index + 1) % frame_count;
            page_faults++;
            print_frames(frames, frame_count);
            printf("\tPage Fault\n");
        } else {
            print_frames(frames, frame_count);
            printf("\tPage Hit\n");
        }
    }

    printf("\nTotal Page Faults (FIFO): %d\n", page_faults);
    printf("Total Page Hits (FIFO): %d\n", page_hits);
    printf("Hit Ratio (FIFO): %.2f%%\n", ((float)page_hits / ref_len) * 100);
}

// LRU Page Replacement Simulation
void simulate_lru(int ref[], int ref_len, int frame_count) {
    int frames[MAX_FRAMES];
    int recent[MAX_FRAMES]; // Tracks last used time/index for each frame
    for (int i = 0; i < frame_count; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    int page_faults = 0;
    int page_hits = 0;

    printf("\n--- LRU Page Replacement Simulation ---\n");
    printf("Ref\tFrames\t\tStatus\n");

    for (int i = 0; i < ref_len; i++) {
        int page = ref[i];
        bool found = false;

        // Check if page is already in frames (Hit)
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == page) {
                found = true;
                recent[j] = i; // Update recent usage timestamp
                page_hits++;
                break;
            }
        }

        printf("%d\t", page);

        if (!found) {
            // Page Fault: Find least recently used frame (minimum recent value)
            int lru_idx = 0;
            int min_time = i + 1;

            for (int j = 0; j < frame_count; j++) {
                if (frames[j] == -1) {
                    lru_idx = j;
                    break;
                }
                if (recent[j] < min_time) {
                    min_time = recent[j];
                    lru_idx = j;
                }
            }

            frames[lru_idx] = page;
            recent[lru_idx] = i;
            page_faults++;
            print_frames(frames, frame_count);
            printf("\tPage Fault\n");
        } else {
            print_frames(frames, frame_count);
            printf("\tPage Hit\n");
        }
    }

    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
    printf("Total Page Hits (LRU): %d\n", page_hits);
    printf("Hit Ratio (LRU): %.2f%%\n", ((float)page_hits / ref_len) * 100);
}

int main() {
    int reference_string[MAX_REF] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int ref_len = MAX_REF;
    int frames = MAX_FRAMES;

    simulate_fifo(reference_string, ref_len, frames);
    simulate_lru(reference_string, ref_len, frames);

    printf("\n=== CONCLUSION ===\n");
    printf("LRU performs better than FIFO because it results in fewer page faults (12 vs 15)\n");
    printf("and a higher hit ratio (40.00%% vs 25.00%%) by replacing the page unused for the longest time.\n");

    return 0;
}
