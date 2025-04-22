
#include <stdio.h>

#define MAX_CARS 10
#define PORTS 3

typedef struct {
    int id;
    int arrivalTime;
    int chargingTime;
    int remainingTime;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
    int isStarted;
} Car;

int allCarsCompleted(Car cars[], int n) {
    for (int i = 0; i < n; i++) {
        if (!cars[i].isCompleted) return 0;
    }
    return 1;
}

int findNextCar(Car cars[], int n, int currentTime) {
    int minTime = 9999, index = -1;
    for (int i = 0; i < n; i++) {
        if (!cars[i].isCompleted && cars[i].arrivalTime <= currentTime) {
            if (cars[i].remainingTime < minTime) {
                minTime = cars[i].remainingTime;
                index = i;
            } else if (cars[i].remainingTime == minTime) {
                if (cars[i].arrivalTime < cars[index].arrivalTime) {
                    index = i;
                }
            }
        }
    }
    return index;
}

int main() {
    Car cars[MAX_CARS] = {
        {1, 0, 4}, {2, 0, 3}, {3, 0, 2}, {4, 1, 1}, {5, 2, 5},
        {6, 3, 2}, {7, 4, 1}, {8, 5, 3}, {9, 6, 2}, {10, 7, 4}
    };

    int n = MAX_CARS;
    for (int i = 0; i < n; i++) {
        cars[i].remainingTime = cars[i].chargingTime;
        cars[i].isCompleted = 0;
        cars[i].isStarted = 0;
    }

    int time = 0;
    int busyPorts = 0;
    int portTimers[PORTS] = {0};
    int portCar[PORTS] = {-1, -1, -1};

    printf("Time\tCharging Ports\n");
    while (!allCarsCompleted(cars, n)) {
        for (int p = 0; p < PORTS; p++) {
            if (portTimers[p] == 0 && portCar[p] != -1) {
                int cid = portCar[p];
                cars[cid].completionTime = time;
                cars[cid].turnaroundTime = cars[cid].completionTime - cars[cid].arrivalTime;
                cars[cid].waitingTime = cars[cid].turnaroundTime - cars[cid].chargingTime;
                cars[cid].isCompleted = 1;
                portCar[p] = -1;
                busyPorts--;
            }
        }

        for (int p = 0; p < PORTS; p++) {
            if (portTimers[p] > 0) portTimers[p]--;
        }

        for (int p = 0; p < PORTS; p++) {
            if (portTimers[p] == 0 && portCar[p] == -1) {
                int cid = findNextCar(cars, n, time);
                if (cid != -1) {
                    portCar[p] = cid;
                    portTimers[p] = cars[cid].remainingTime;
                    cars[cid].startTime = time;
                    cars[cid].isStarted = 1;
                    busyPorts++;
                }
            }
        }

        printf("%2d\t", time);
        for (int p = 0; p < PORTS; p++) {
            if (portCar[p] != -1) {
                printf("C%d ", cars[portCar[p]].id);
            } else {
                printf("-- ");
            }
        }
        printf("\n");

        time++;
    }

    printf("\nCar\tAT\tCT\tST\tCTime\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("C%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               cars[i].id, cars[i].arrivalTime, cars[i].chargingTime,
               cars[i].startTime, cars[i].completionTime,
               cars[i].waitingTime, cars[i].turnaroundTime);
    }

    // Average times
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += cars[i].waitingTime;
        totalTAT += cars[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
