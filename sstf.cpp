#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int n = sizeof(requests) / sizeof(requests[0]);
    int total_seek_time = 0;
    int completed[n];

    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX;
        int next_request = -1;

        for (int j = 0; j < n; j++) {
            if (!completed[j]) {
                int distance = abs(requests[j] - head);
                if (distance < min_distance) {
                    min_distance = distance;
                    next_request = j;
                }
            }
        }
        total_seek_time += min_distance;
        head = requests[next_request];
        completed[next_request] = 1;
    }

    printf("Total seek time: %d\n", total_seek_time);
    printf("Average seek time: %.2f\n", (float)total_seek_time / n);

    return 0;
}