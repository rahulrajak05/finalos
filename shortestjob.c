#include <stdio.h>

void main() {
    int n, b[10], w[10], i, j, h, t, tt;
    int stime[10], a[10];
    float avg = 0;

    printf("\n\tJOB SCHEDULING ALGORITHM [SJF]");
    printf("\n\t*****************************************************\n");
    printf("\nEnter how many jobs: ");
    scanf("%d", &n);
    printf("\nEnter burst time for corresponding job....\n");

    for(i = 0; i < n; i++) {
        printf("\nProcess %d: ", i + 1);
        scanf("%d", &b[i]);
        a[i] = i + 1;  // Store process number for later use
    }

    // Sorting burst time using simple bubble sort
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(b[i] > b[j]) {
                t = b[i];
                b[i] = b[j];
                b[j] = t;
                tt = a[i];
                a[i] = a[j];
                a[j] = tt;
            }
        }
    }

    w[0] = 0;  // First process has a waiting time of 0
    printf("\nProcess %d waiting time is 0", a[0]);
    
    // Calculate waiting times
    for(i = 1; i < n; i++) {
        w[i] = b[i - 1] + w[i - 1];
        printf("\nProcess %d waiting time: %d", a[i], w[i]);
        avg += w[i];  // Add to total waiting time
    }

    printf("\nTotal waiting time: %.2f", avg);
    printf("\n\nThe average waiting time is: %.2f\n", avg / n);

    // Gantt Chart
    printf("\nGantt Chart\n***************************************\n\n\t");
    h = 22;  // To represent the process in a graphical form

    // Display Gantt chart representation (each process as 'x')
    for(i = 0; i < n; i++) {
        printf("%d", b[i]);
        for(j = 0; j < b[i]; j++) {
            printf("%c", h);  // Display a process
        }
    }

    printf("\n\t");

    // Print process starting time line (0, 1, 2, etc.)
    for(i = 0; i < n; i++) {
        printf("%d", w[i]);
        for(j = 0; j < b[i]; j++) {
            printf("%c", h);
        }
    } 

    printf("\n");
}


