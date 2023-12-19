#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//unique username

void Menu(void);
char *StrToUpper(char *str);
void checkAccountNo(char *accStr);
void SAVE();

typedef struct
{
    int month,year;
} Date;

typedef struct
{
    char mobile_number[12];
    char account_number[11];
    char username[20];
    char email_address[30];
    double balance;
    Date dateOpened;
    FILE *fptr ;

} Account;

//Will be mainly used in ADD function
Account *ConstructAccount(char *mobile, char *accNum, char *name, char *email, double balanceNum, Date *dateOpnd)
{
    //Reserving memory in the heap for new instance
    Account *acc = malloc(sizeof(Account));
    if (acc == NULL)
    {
        printf("No enough space!\n");
        return NULL;
    }
    //Copying the arguments into the new instance arguments
    strcpy(acc->account_number, accNum);
    strcpy(acc->mobile_number, mobile);
    strcpy(acc->email_address, email);
    strcpy(acc->username, name);
    acc->balance = balanceNum;
    acc->dateOpened.month = dateOpnd->month;
    acc->dateOpened.year = dateOpnd->year;

    return acc;
}


//Will be used before closing the program
void DestructAccount(Account *acc)
{
    free(acc);
}

int main()
{
    char accnum[20];
    Account array[50];

    //gets(accnum);
    //checkAccountNo(accnum);
    Menu();
    return 0;
}

void Menu(void)
{
    char choice[20];
    int flag;

    printf("%s", "Please select one of the following options(Enter the EXACT name of desired option):\n");
    printf("%s", " - ADD\n - DELETE\n - MODIFY\n - SEARCH\n - ADVANCED SEARCH\n - WITHDRAW\n");
    printf("%s", " - DEPOSIT\n - TRANSFER\n - REPORT\n - PRINT\n - QUIT\n");



    do
    {
        flag = 1;
        printf("Desired option: ");
        gets(choice);
        StrToUpper(choice);

        if (strcmp(choice, "ADD") == 0)
            printf("ADD\n");

        else if (strcmp(choice, "DELETE") == 0)
            printf("DELETE\n");

        else if (strcmp(choice, "MODIFY") == 0)
            printf("MODIFY\n");

        else if (strcmp(choice, "SEARCH") == 0)
            printf("SEARCH\n");

        else if (strcmp(choice, "ADVANCED SEARCH") == 0)
            printf("ADVANCED SEARCH\n");

        else if (strcmp(choice, "WITHDRAW") == 0)
            printf("WITHDRAW\n");

        else if (strcmp(choice, "DEPOSIT") == 0)
            printf("DEPOSIT\n");

        else if (strcmp(choice, "TRANSFER") == 0)
            printf("TRANSFER\n");

        else if (strcmp(choice, "REPORT") == 0)
            printf("REPORT\n");

        else if (strcmp(choice, "PRINT") == 0)
            printf("PRINT\n");

        else if (strcmp(choice, "QUIT") == 0)
            printf("QUIT\n");

        else
        {
            printf("%s", "Invalid Option Entered!\n");
            flag = 0;
        }
    }
    while (!flag);
}

void checkAccountNo(char *accStr)
{
    for (size_t i = 0; *(accStr + i) != '\0'; i++)
    {
        if (!(isdigit(*(accStr + i)) == 1))
            printf("Invalid Account Number!(Should be numbers ONLY)\n");
    }
    if (strlen(accStr) != 10)
        printf("Invalid Account Number!(Should be 10-Digits)\n");

}

char *StrToUpper(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        *(str + i) = toupper(*(str + i));
    return str;
}
