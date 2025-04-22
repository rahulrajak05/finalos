#include <stdio.h>

void main()
{
    int n, b[10], w[10], i, j, h;
    float avg = 0;
    printf("\n\tJOB SCHEDULING ALGORITHM[FCFS]");
    printf("\n\t*****************************************************\n");
    printf("\nEnter how many jobs: ");
    scanf("%d", &n);

    printf("\nEnter burst time for corresponding job....\n");
    for (i = 0; i < n; i++) {
        printf("\nProcess %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    w[0] = 0;  // The waiting time for the first process is always 0
    printf("\nProcess 1 waiting time is 0");

    // Calculate waiting time for each process, 
    for (i = 1; i < n; i++) {
        w[i] = b[i - 1] + w[i - 1];
        printf("\nProcess %d waiting time: %d", i + 1, w[i]);
        avg += w[i];
    }

    // Calculate the average waiting time
    printf("\nTotal waiting time: %f", avg);
    printf("\n\nThe average waiting time is: %f\n", avg / n);

    // Generate Gantt Chart
    printf("\nGantt Chart\n***************************************\n\n\t");
    h = 22;  // Character used for the chart

    // Print the burst time in the chart
    for (i = 0; i < n; i++) {
        printf("%d", b[i]);
        for (j = 1; j <= b[i]; j++)
            printf("%c", h);
    }

    printf("\n\t");
    // Print the waiting time in the chart
    for (i = 0; i < n; i++) {
        printf("%d", w[i]);
        for (j = 1; j <= w[i]; j++)
            printf("%c", h);
    }
    printf("\n");
}
