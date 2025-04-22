
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int priority;
    int burst_time;
    int remaining_time;
} Process;

void schedule(Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].priority > highestPriority) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++;
        } else {
            processes[highestPriorityIndex].remaining_time--;
            currentTime++;

            if (processes[highestPriorityIndex].remaining_time == 0) {
                completed++;
                printf("Process %d completed at time %d\n", processes[highestPriorityIndex].pid, currentTime);
            }
        }
    }
}

int main() {
    Process processes[] = {
        {1, 3, 10, 10},
        {2, 1, 5, 5},
        {3, 2, 8, 8}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    schedule(processes, n);

    return 0;
}