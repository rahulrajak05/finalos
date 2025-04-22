
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, max_track;
    int direction; // 0 for left, 1 for right
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the disk request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the maximum track number: ");
    scanf("%d", &max_track);
     printf("Enter the initial direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
    int total_movement = 0;
    int current = head;
    int index = 0;

    if (direction == 1) { // Move right initially
        while (index < n && requests[index] <= current) {
            index++;
        }
        for (int i = index; i < n; i++) {
            total_movement += abs(current - requests[i]);
            current = requests[i];
        }
        if (index > 0) {
           total_movement += abs(current - requests[index - 1]);
           current = requests[index - 1];
        }
        for (int i = index - 2; i >= 0; i--) {
            total_movement += abs(current - requests[i]);
            current = requests[i];
        }
    } else { // Move left initially
        int i = n - 1;
        while (i >= 0 && requests[i] >= current) {
            i--;
        }
        for (int j = i; j >= 0; j--) {
            total_movement += abs(current - requests[j]);
            current = requests[j];
        }
         if (i < n - 1) {
            total_movement += abs(current - requests[i + 1]);
            current = requests[i + 1];
        }
        for (int j = i + 2; j < n; j++) {
            total_movement += abs(current - requests[j]);
            current = requests[j];
        }
    }
    printf("Total head movement: %d\n", total_movement);
    return 0;
}