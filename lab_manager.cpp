
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PROJECTS 100
#define MAX_NAME 100

void createProject(const char *projectName, const char *role) {
    char cmd[256];

    // Create project folder
    snprintf(cmd, sizeof(cmd), "mkdir -p %s/{data,scripts,results}", projectName);
    if (system(cmd) != 0) {
        printf("❌ Error: Failed to create project structure.\n");
        return;
    }

    // Set permissions
    snprintf(cmd, sizeof(cmd), "chmod 770 %s", projectName);
    system(cmd);

    snprintf(cmd, sizeof(cmd), "chmod 770 %s/data", projectName);
    system(cmd); // data: rwx for owner/group

    snprintf(cmd, sizeof(cmd), "chmod 750 %s/scripts", projectName);
    system(cmd); // scripts: r-x for group

    snprintf(cmd, sizeof(cmd), "chmod 570 %s/results", projectName);
    system(cmd); // results: r-x for group

    printf("✅ Project '%s' created successfully with role-based access.\n", projectName);
}

void deleteProject(const char *projectName, const char *role) {
    if (strcmp(role, "admin") != 0) {
        printf("⛔ Error: Only admin can delete project directories.\n");
        return;
    }
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "rm -rf %s", projectName);
    if (system(cmd) == 0) {
        printf("✅ Project '%s' deleted successfully.\n", projectName);
    } else {
        printf("❌ Error deleting project.\n");
    }
}

void listProjects() {
    printf("📂 Existing Projects:\n");
    system("ls -d */ 2>/dev/null");
}

int main() {
    char role[20];
    char projectName[MAX_NAME];
    int choice;

    printf("🔐 Enter your role (admin / lead / researcher): ");
    scanf("%s", role);

    while (1) {
        printf("\n🔧 MENU:\n");
        printf("1. Create Project Directory\n");
        printf("2. Delete Project Directory\n");
        printf("3. List Projects\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Flush newline

        switch (choice) {
            case 1:
                printf("Enter new project name: ");
                scanf("%s", projectName);
                createProject(projectName, role);
                break;
            case 2:
                printf("Enter project name to delete: ");
                scanf("%s", projectName);
                deleteProject(projectName, role);
                break;
            case 3:
                listProjects();
                break;
            case 4:
                printf("🚪 Exiting...\n");
                return 0;
            default:
                printf("❗ Invalid choice. Try again.\n");
        }
    }

    return 0;
}
