
#include <stdio.h>
#include <stdlib.h>

// Structure for a process
typedef struct {
    int pid;        // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int priority;     // Priority
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
} Process;

// Function to calculate waiting time for each process
void calculateWaitingTime(Process processes[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrival_time) {
            currentTime = processes[i].arrival_time;
        }
        processes[i].waiting_time = currentTime - processes[i].arrival_time;
        currentTime += processes[i].burst_time;
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

// Function to sort processes based on arrival time (for FCFS)
void sortByArrivalTime(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to sort processes based on burst time (for SJF)
void sortByBurstTime(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to sort processes based on priority (for Priority Scheduling)
void sortByPriority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    printf("Enter process details (Arrival Time, Burst Time, Priority):\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }

    printf("\nChoose scheduling algorithm:\n");
    printf("1. First-Come, First-Served (FCFS)\n");
    printf("2. Shortest-Job-First (SJF)\n");
    printf("3. Priority Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // FCFS
            sortByArrivalTime(processes, n);
            calculateWaitingTime(processes, n);
            calculateTurnaroundTime(processes, n);
            break;
        case 2: // SJF
            sortByBurstTime(processes, n);
            calculateWaitingTime(processes, n);
            calculateTurnaroundTime(processes, n);
            break;
        case 3: // Priority Scheduling
            sortByPriority(processes, n);
            calculateWaitingTime(processes, n);
            calculateTurnaroundTime(processes, n);
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].waiting_time,
               processes[i].turnaround_time);
    }

    return 0;
}