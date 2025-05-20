#include <stdio.h>
#include <stdlib.h>

#define MAX_REF_LEN 100
#define MAX_FRAMES 10

// Function to check if a page is already in memory
int isInMemory(int page, int memory[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (memory[i] == page) return 1;
    }
    return 0;
}

// FIFO Page Replacement
void simulateFIFO(int pages[], int n, int frameCount) {
    int memory[MAX_FRAMES];
    int front = 0, faults = 0;

    for (int i = 0; i < frameCount; i++)
        memory[i] = -1;

    printf("\n--- FIFO Simulation ---\n");

    for (int i = 0; i < n; i++) {
        printf("Page %d: ", pages[i]);

        if (!isInMemory(pages[i], memory, frameCount)) {
            memory[front] = pages[i];
            front = (front + 1) % frameCount;
            faults++;
        }

        for (int j = 0; j < frameCount; j++) {
            if (memory[j] == -1)
                printf(" - ");
            else
                printf(" %d ", memory[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", faults);
}

// Helper function for LRU: returns the index of least recently used page
int findLRU(int time[], int frameCount) {
    int min = time[0], pos = 0;
    for (int i = 1; i < frameCount; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

// LRU Page Replacement
void simulateLRU(int pages[], int n, int frameCount) {
    int memory[MAX_FRAMES];
    int time[MAX_FRAMES];
    int count = 0, faults = 0;

    for (int i = 0; i < frameCount; i++) {
        memory[i] = -1;
        time[i] = 0;
    }

    printf("\n--- LRU Simulation ---\n");

    for (int i = 0; i < n; i++) {
        int flag = 0;
        printf("Page %d: ", pages[i]);

        for (int j = 0; j < frameCount; j++) {
            if (memory[j] == pages[i]) {
                count++;
                time[j] = count;
                flag = 1;
                break;
            }
        }

        if (!flag) {
            int pos = findLRU(time, frameCount);
            memory[pos] = pages[i];
            count++;
            time[pos] = count;
            faults++;
        }

        for (int j = 0; j < frameCount; j++) {
            if (memory[j] == -1)
                printf(" - ");
            else
                printf(" %d ", memory[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", faults);
}

int main() {
    int pages[MAX_REF_LEN], n, frameCount;

    printf("Enter number of page references: ");
    scanf("%d", &n);

    printf("Enter the page reference sequence (space-separated):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames in memory: ");
    scanf("%d", &frameCount);

    simulateFIFO(pages, n, frameCount);
    simulateLRU(pages, n, frameCount);

    return 0;
}
