#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>   // For directory operations
#include <sys/stat.h> // For file operations

void copy_file();
void move_file();
void print_file();

char fn2[20];  // To store the destination file name1

int main() {
    int c;
    do {
        printf("\n\t\tMain Menu\n-------------------------------\n");
        printf("1. Copy a File\n");
        printf("2. Move a File\n");
        printf("3. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                copy_file();
                break;

            case 2:
                move_file();
                break;

            case 3:
                exit(0);
        }
    } while (c <= 3);
    return 0;
}

void copy_file() {
    FILE *f1, *f2;
    char ch, fn1[20];
    int a;

    printf("\nDo you want to see the previous files? (1/0): ");
    scanf("%d", &a);
    if (a == 1) {
        print_file();
    }

    printf("Enter the source file name: ");
    scanf("%s", fn1);  // Read source file name
    printf("Enter the destination file name: ");
    scanf("%s", fn2);  // Read destination file name

    f1 = fopen(fn1, "r");
    if (f1 == NULL) {
        printf("Can't open the source file.\n");
    } else {
        f2 = fopen(fn2, "w");
        while ((ch = getc(f1)) != EOF) {
            putc(ch, f2);  // Copy content to the destination file
        }
        printf("File copied successfully.\n");
        fclose(f2);
        fclose(f1);
    }
}

void move_file() {
    FILE *f1, *f2;
    char ch, fn1[20];
    int a;

    printf("\nDo you want to see the previous files? (1/0): ");
    scanf("%d", &a);
    if (a == 1) {
        print_file();
    }

    printf("Enter the source file name: ");
    scanf("%s", fn1);  // Read source file name
    printf("Enter the destination file name: ");
    scanf("%s", fn2);  // Read destination file name

    f1 = fopen(fn1, "r");
    if (f1 == NULL) {
        printf("Can't open the source file.\n");
    } else {
        f2 = fopen(fn2, "w");
        while ((ch = getc(f1)) != EOF) {
            putc(ch, f2);  // Copy content to the destination file
        }
        printf("File moved successfully.\n");
        fclose(f2);
        fclose(f1);
        remove(fn1);  // Delete the original file
    }
}

void print_file() {
    DIR *dp;
    struct dirent *entry;
    int p = 0;

    // Open current directory
    dp = opendir(".");
    if (dp == NULL) {
        printf("Couldn't open the directory.\n");
        return;
    }

    printf("Listing files in the current directory:\n");

    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);  // Print file names
        p++;
        if (p >= 20) {  // Limit the output to 20 files per screen
            printf("Press Enter to continue...");
            getchar();  // Wait for user input to continue
            p = 0;
        }
    }

    closedir(dp);  // Close the directory
}
