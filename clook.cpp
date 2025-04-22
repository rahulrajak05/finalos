
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to sort the request array
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, head, max_tracks, direction;

    // Get the number of requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    // Allocate memory for the request array
    int *requests = (int *)malloc(n * sizeof(int));
    if (requests == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Get the disk requests
    printf("Enter the disk request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Get the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Get the maximum number of tracks
    printf("Enter the maximum number of tracks: ");
    scanf("%d", &max_tracks);

    // Get the direction (0 for left, 1 for right)
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Sort the requests
    sort(requests, n);

    int total_movement = 0;
    int current_pos = head;
    int index;

    // Find the index of the first request greater than or equal to the head position
    for (index = 0; index < n; index++) {
        if (requests[index] >= head) {
            break;
        }
    }
    
    printf("Seek Sequence: %d -> ", head);

    if (direction == 1) { // Moving right
        // Serve requests to the right
        for (int i = index; i < n; i++) {
            total_movement += abs(current_pos - requests[i]);
            current_pos = requests[i];
            printf("%d ", current_pos);
            if (i < n - 1) printf("-> ");
        }
        
        // Serve requests to the left
        for (int i = 0; i < index; i++) {
             total_movement += abs(current_pos - requests[i]);
             current_pos = requests[i];
             printf("%d ", current_pos);
             if (i < index - 1) printf("-> ");
        }

    } else { // Moving left
        // Serve requests to the left
        for (int i = index - 1; i >= 0; i--) {
            total_movement += abs(current_pos - requests[i]);
            current_pos = requests[i];
            printf("%d ", current_pos);
             if (i > 0) printf("-> ");
        }

        // Serve requests to the right
        for (int i = n - 1; i >= index; i--) {
            total_movement += abs(current_pos - requests[i]);
            current_pos = requests[i];
            printf("%d ", current_pos);
            if (i > index) printf("-> ");
        }
    }

    printf("\nTotal head movement: %d\n", total_movement);

    free(requests);

    return 0;
}