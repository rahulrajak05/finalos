#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, b[10], w[10], i, j;
    float avg = 0;

    printf("\n\tJOB SCHEDULING ALGORITHM [FCFS]");
    printf("\n\t*\n");

    printf("\nEnter the number of jobs: ");
    scanf("%d", &n);

    printf("\nEnter burst time for each job:\n");
    for (i = 0; i < n; i++)
    {
        printf("\nProcess %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    w[0] = 0;
    printf("\nProcess 1 waiting time: 0");
    for (i = 1; i < n; i++)
    {
        w[i] = b[i - 1] + w[i - 1];
        printf("\nProcess %d waiting time: %d", i + 1, w[i]);
        avg += w[i];
    }

    printf("\nTotal waiting time: %.2f", avg);
    printf("\n\nThe average waiting time is: %.2f\n", avg / n);

    printf("\nGantt Chart\n*\n\n\t");
    for (i = 0; i < n; i++)
    {
        printf("| P%d ", i + 1);
    }
    printf("|\n\t");

    int time = 0;
    printf("0 ");
    for (i = 0; i < n; i++)
    {
        time += b[i];
        printf("   %d ", time);
    }
    printf("\n");

    return 0;
}
