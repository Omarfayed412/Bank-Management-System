#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Login( char *loginUsername, char *loginPassword)
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(0);
    }

    char Username[50];
    char Password[50];

    while (fscanf(file, "%s %s", Username, Password) == 2)
    {

        if (strcmp(loginUsername, Username) == 0 && strcmp(loginPassword, Password) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    exit(0);
}

int main()
{

    char username[50];
    char password[50];

    printf("Welcome to Bank Management System :)\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (Login(username, password))
    {
        printf("Login successful!\n");

    }
    else
    {
        printf("Invalid username or password.\n");
    }

    return 0;
}
