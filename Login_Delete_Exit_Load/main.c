#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month;
    int year;
};

struct User
{
    char username[50];
    char password[50];   // i dont know if it should be 50 or more
};

struct Account
{
    int accountNumber;
    char name[50];
    char email[50];
    float balance;
    char mobile[15];
    struct Date dateOpened;
};

int read(struct User *users, int *numUsers)
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening users.txt\n");
        exit(1);
    }

    while (fscanf(file, "%s %s", users[*numUsers].username, users[*numUsers].password) == 2)
    {
        (*numUsers)++;
    }

    fclose(file);
}


int login(struct User *users, int numUsers)
{
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void deleteAccount(struct Account *accounts, int *numAccounts)
{
    int accountNumber;
    printf("Enter account number to delete: ");
    scanf("%d", &accountNumber);

    int index = -1;
    for (int i = 0; i < *numAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Account not found.\n");
        return;
    }

    if (accounts[index].balance > 0)
    {
        printf("Cannot delete account with a non-zero balance.\n");
        return;
    }

    for (int i = index; i < *numAccounts - 1; i++)
    {
        accounts[i] = accounts[i + 1];
    }

    (*numAccounts)--;
    printf("Account deleted successfully.\n");
}

void loadAccounts(struct Account *accounts, int *numAccounts)
{
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL)
    {
        printf("Error opening accounts.txt\n");
        exit(1);
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%14[^,],%d-%d",
                  &accounts[*numAccounts].accountNumber,
                  accounts[*numAccounts].name,
                  accounts[*numAccounts].email,
                  &accounts[*numAccounts].balance,
                  accounts[*numAccounts].mobile,
                  &accounts[*numAccounts].dateOpened.month,
                  &accounts[*numAccounts].dateOpened.year) == 6)
    {
        (*numAccounts)++;
    }

    fclose(file);
}

int main()
{
    struct User users[100];
    int numUsers = 0;

    struct Account accounts[100]; // max users i dont know if it should be 100 or more :/
    int numAccounts = 0;

    read(users, &numUsers);


    int choice;

    do
    {
        printf("======================\nBank Management System\n======================\n");
        printf("1. Login\n");
        printf("2. Load (Read from file)\n");
        printf("3. Delete\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (login(users, numUsers))
            {
                printf("Login successful!\n");

            }
            else
            {
                printf("Invalid username or password. \nLogin failed.\n");
            }
            break;
        case 2:
            loadAccounts(accounts, &numAccounts);
            printf("Accounts loaded successfully.\n");
            break;
        case 3:
            deleteAccount(accounts, &numAccounts);
            break;
        case 4:
            printf("Exiting, thank you for using our system.\n");
            break;
        default:
            printf("Invalid choice.\n Please try again.\n");
        }
    }
    while (choice != 4);

    return 0;
}
