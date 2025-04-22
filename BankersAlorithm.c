#include <stdio.h>

void calculateNeed(int need[][10], int max[][10], int allocation[][10], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe(int processes[], int available[], int max[][10], int allocation[][10], int n, int m) {
    int need[n][m];
    calculateNeed(need, max, allocation, n, m);

    int finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int safeSequence[n];
    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }

                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = processes[p];
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            printf("The system is not in a safe state.\n");
            return 0;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return 1;
}

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int processes[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }

    int allocation[n][10], max[n][10], available[10];
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    isSafe(processes, available, max, allocation, n, m);

    return 0;
}