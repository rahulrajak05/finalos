#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <sys/stat.h>  // For chmod
#include <errno.h>      // For perror

void main() {
    char name[100];
    int n;
    mode_t attrib = 0;


    printf("\t\tMAIN MENU OF PERMISSION\n\t--------------------------------\n");
    printf("1. Only Read\n");
    printf("2. Only Write\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &n);

    switch (n) {
        case 1:  // Read permission
            printf("\nEnter the File Name: ");
            scanf("%s", name);
            attrib = S_IRUSR;
            printf("%s file read permission Accepted\n", name);
            break;

        case 2:
            printf("\nEnter the File Name: ");
            scanf("%s", name);
            attrib = S_IWUSR;
            printf("%s write permission Accepted\n", name);
            break;

        case 3:
            exit(0);
            break;

        default:
            printf("\nInvalid choice! Exiting...\n");
            exit(1);
    }


    if (chmod(name, attrib) != 0) {
        perror("\nUnable to set file attribute");
        getch();
        return;
    }

    getch();
}
