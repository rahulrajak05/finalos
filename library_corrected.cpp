#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_STUDENTS 15
#define MAX_ROOMS 5

typedef struct {
    int id;
    int studyTime;
} Student;

int N = 3;  // Number of study rooms (can be updated)
int M = 10; // Number of students (can be updated)

sem_t availableRooms;
pthread_mutex_t queueLock;
int queueOrder = 0;

// Fair Queueing using condition variables
pthread_cond_t cond[MAX_STUDENTS];
int turn[MAX_STUDENTS];

void* studentThread(void* arg) {
    Student* s = (Student*)arg;
    int id = s->id;
    int myTurn;

    // Lock the queue to assign a turn
    pthread_mutex_lock(&queueLock);
    myTurn = queueOrder;
    turn[id] = myTurn;
    queueOrder++;
    while (1) {
        int canGo = 1;
        for (int i = 0; i < M; i++) {
            if (turn[i] < turn[id]) {
                canGo = 0;
                break;
            }
        }
        if (canGo) break;
        pthread_cond_wait(&cond[id], &queueLock);
    }
    pthread_mutex_unlock(&queueLock);

    // Wait for room availability
    sem_wait(&availableRooms);

    printf("Student %d enters room and studies for %d seconds\n", id + 1, s->studyTime);
    sleep(s->studyTime);
    printf("Student %d leaves the room\n", id + 1);

    sem_post(&availableRooms); // Release the room

    // Wake up the next student in the queue
    pthread_mutex_lock(&queueLock);
    for (int i = 0; i < M; i++) {
        if (turn[i] > myTurn) {
            pthread_cond_signal(&cond[i]);
        }
    }
    pthread_mutex_unlock(&queueLock);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_STUDENTS];
    Student students[MAX_STUDENTS];

    printf("Enter number of study rooms (N ≤ %d): ", MAX_ROOMS);
    scanf("%d", &N);
    if (N > MAX_ROOMS || N <= 0) {
        printf("Invalid number of study rooms. Exiting.\n");
        return 1;
    }

    printf("Enter number of students (M > N, M ≤ %d): ", MAX_STUDENTS);
    scanf("%d", &M);
    if (M > MAX_STUDENTS || M <= N) {
        printf("Invalid number of students. Exiting.\n");
        return 1;
    }

    sem_init(&availableRooms, 0, N);
    pthread_mutex_init(&queueLock, NULL);
    for (int i = 0; i < MAX_STUDENTS; i++) {
        pthread_cond_init(&cond[i], NULL);
        turn[i] = 9999; // Initialize turn array with a high value
    }

    printf("\nLibrary Simulation Starting...\n\n");

    for (int i = 0; i < M; i++) {
        students[i].id = i;
        students[i].studyTime = (rand() % 5) + 1; // Random study time (1-5 seconds)
        pthread_create(&threads[i], NULL, studentThread, &students[i]);
        sleep(1); // Stagger arrivals for realism
    }

    for (int i = 0; i < M; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nLibrary Simulation Ended.\n");

    sem_destroy(&availableRooms);
    pthread_mutex_destroy(&queueLock);
    for (int i = 0; i < MAX_STUDENTS; i++) {
        pthread_cond_destroy(&cond[i]);
    }

    return 0;
}
