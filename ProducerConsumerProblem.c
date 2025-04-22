#include <stdio.h>
#include <stdlib.h>
void display(int count, int stack[], int size);
int main() {
    int ch, n, c1 = 0, c2 = 0, produce[23], consume[23];
    printf("Enter Stack Size: ");
    scanf("%d", &n);
    while (1) {
        printf("\t\tProducer Stack (Stack Size: %d)\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", n);
        display(c1, produce, n);
        printf("\n\n\t\tConsumer Stack (Stack Size: %d)\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", n);
        display(c2, consume, n);
        printf("\n\t\tCHOICES\n\t\t~~~~~~~\n\t1. Producer\n\t2. Consumer\n\t3. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                if (c1 == n) {
                    printf("\nProducer stack is FULL. So Producer goes to SLEEP.\n");
                } else {
                    printf("\t\tEnter PRODUCE item: ");/;
                    scanf("%d", &produce[c1]);
                    c1++;
                }
                break;
            case 2:
                if (c2 == n) {
                    printf("\nConsumer Stack is FULL. So it goes to SLEEP!\n");
                } else if (c1 == 0) {
                    printf("\nProducer stack is EMPTY.\n");
                } else {
                    c2++;
                    consume[c2 - 1] = produce[c1 - 1];
                    printf("\t\tCONSUME one item: %d\n", consume[c2 - 1]);
                    c1--;
                }
                break;
            case 3:
                exit(0);
            default:
                printf("\tInvalid choice! Please enter a correct option.\n");
        }
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
    return 0;
}
void display(int count, int stack[], int size) {
    printf("\n--------------------------------------------------------------------------\n");
    if (count == 0) {
        printf("\tStack is EMPTY\n\t\t(Now It is sleeping)");
    } else {
        for (int i = 0; i < count; i++) {
            printf("\t%d", stack[i]);
        }
    }
    printf("\n--------------------------------------------------------------------------\n");
}

