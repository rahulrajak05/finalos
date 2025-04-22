#include <stdio.h>

int findOptimalIndex(int frames[], int capacity, int pages[], int n, int currentIndex) {
    int farthest = currentIndex, index = -1;

    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = currentIndex + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n) {
            return i; // If a frame is not used in the future, return its index
        }
    }

    return (index == -1) ? 0 : index; // If all frames are used, return the farthest one
}

void Optimal_PageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];
    int pageFaults = 0;

    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    printf("Page Reference String | Frames\n");
    printf("-----------------------|-----------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found, replace the optimal page
        if (!found) {
            if (i < capacity) {
                frames[i] = page; // Fill empty frames first
            } else {
                int index = findOptimalIndex(frames, capacity, pages, n, i);
                frames[index] = page; // Replace the optimal page
            }
            pageFaults++;
        }

        // Print the current state of frames
        printf("         %d            | ", page);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    Optimal_PageReplacement(pages, n, capacity);

    return 0;
}