#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#ifdef _WIN32  // Check if the system is Windows
#include <direct.h>
#else
#include <sys/stat.h>  // For Linux/MacOS mkdir
#endif

void list_file();
void directory();
void change_dir();
void subfun(char *s);

int main() {
    int ch;
    do {
        printf("\n\t\t\tMAIN MENU\n\t\t-------------------------\n");
        printf("1. To Display List of Files\n");
        printf("2. To Create New Directory\n");
        printf("3. To Change the Working Directory\n");
        printf("4. Exit\n");
        printf("Enter the Number: ");
        scanf("%d", &ch);
        
        switch (ch) {
            case 1:
                list_file();
                break;

            case 2:
                directory();
                break;

            case 3:
                change_dir();
                break;

            case 4:
                exit(0);
        }
    } while (ch <= 4);
    return 0;
}

void list_file() {
    int l;
    char e[100] = ".";
    printf("\t\tLIST FILE DETAIL\n\t--------------------------------------\n");
    printf("1. List All Files\n2. List of Extension Files\n3. List of Name Wise\n");
    scanf("%d", &l);
    
    switch (l) {
        case 1:
            printf("List of All (.) Files\n");
            subfun(e);
            break;

        case 2:
            printf("Enter the Extension: ");
            scanf("%s", e);
            subfun(e);
            break;

        case 3:
            printf("Enter the Name wise (eg: moha*.*): ");
            scanf("%s", e);
            subfun(e);
            break;
    }
}

void directory() {
    char name[100];
    struct stat st;
    printf("Enter the Directory name: ");
    scanf("%s", name);

    // Check if directory exists using opendir
    DIR *dir = opendir(name);
    if (dir) {
        // Directory exists
        printf("%s Directory already exists\n", name);
        closedir(dir);
    } else {
        // Directory doesn't exist, create it
        #ifdef _WIN32
            if (_mkdir(name) == 0) {  // Windows uses _mkdir
                printf("%s Directory Successfully Created\n", name);
            } else {
                printf("Failed to create directory\n");
            }
        #else
            if (mkdir(name, 0777) == 0) {  // Linux/MacOS uses mkdir
                printf("%s Directory Successfully Created\n", name);
            } else {
                printf("Failed to create directory\n");
            }
        #endif
    }
}

void change_dir() {
    char buffer[1024];
    int d;
    printf("\nCurrent Directory: %s\n", getcwd(buffer, sizeof(buffer)));
    printf("\t\tChange Directory\n\t\t-----------------\n");
    printf("\n1. Step by Step Backward\n2. Go to Root Directory\n3. Forward Directory\nEnter the number: ");
    scanf("%d", &d);
    
    switch (d) {
        case 1:
            chdir("..");
            break;

        case 2:
            chdir("/");
            break;

        case 3:
            printf("Please enter the Directory name: ");
            scanf("%s", buffer);
            chdir(buffer);
            break;
    }

    printf("\nCurrent Directory: %s\n", getcwd(buffer, sizeof(buffer)));
}

void subfun(char *s) {
    struct dirent *entry;
    DIR *dp;
    int p = 0, i = 0;

    dp = opendir(".");
    if (dp == NULL) {
        printf("Failed to open directory\n");
        return;
    }

    while ((entry = readdir(dp))) {
        if (strstr(entry->d_name, s)) {
            printf("%s\n", entry->d_name);
            i++;
            p++;
            if (p >= 22) {
                printf("Press Enter to continue...\n");
                getchar(); // Wait for the user to press enter
                p = 0;
            }
        }
    }

    closedir(dp);
    printf("\nTotal Files: %d\n", i);
}