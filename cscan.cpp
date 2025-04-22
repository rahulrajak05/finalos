
#include <stdio.h>
#include <stdlib.h>

int main() {
    int requests[20], n, head, max_tracks, direction;
    int total_seek_time = 0, i, j;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the maximum number of tracks: ");
    scanf("%d", &max_tracks);

    printf("Enter the direction (1 for right/high, 0 for left/low): ");
    scanf("%d", &direction);

    // Sort the requests
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    if (direction == 1) { // Moving right
        for (i = 0; i < n; i++) {
            if (requests[i] >= head) {
                total_seek_time += abs(requests[i] - head);
                head = requests[i];
            }
        }
        total_seek_time += abs(max_tracks - 1 - head);
        head = 0;
        for (i = 0; i < n; i++) {
            if (requests[i] < max_tracks) {
                total_seek_time += abs(requests[i] - head);
                head = requests[i];
            }
        }
    } else { // Moving left
        for (i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                total_seek_time += abs(requests[i] - head);
                head = requests[i];
            }
        }
        total_seek_time += abs(head - 0);
        head = max_tracks - 1;
        for (i = n - 1; i >= 0; i--) {
            if (requests[i] > 0) {
                total_seek_time += abs(requests[i] - head);
                head = requests[i];
            }
        }
    }

    printf("Total seek time: %d\n", total_seek_time);

    return 0;
}