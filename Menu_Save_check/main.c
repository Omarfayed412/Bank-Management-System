#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//unique username

void Menu(void);
char *StrToUpper(char *str);
void checkAccountNo(char *accStr);
//void SAVE();

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
    FILE *f_report ;

} Account;

Account *constructAccount(char *mobile, char *accNum, char *name, char *email, double balanceNum, Date *dateOpnd);
void destructAccount(Account *acc);
void retrieveData(Account *array, size_t size);
void printUsertest(Account *user);

//used throughout the program to calculate available places in the accounts array
unsigned int acCount = 0;

int main()
{
    //Defining an array of objects to hold the data
    size_t size = 50;
    Account accounts[size];

    retrieveData(accounts, size);

    for (size_t i = 0; i < 2; i++){
        printUsertest(accounts + i);
    }

    return 0;
}

void retrieveData(Account *array, size_t size){
    FILE *fptr = fopen("accounts.txt", "r");
    if (fptr == NULL){
        printf("Couldn't find database file!\n");
        exit(-1);
    }

    char buffer[200];
    size_t i = 0, j;

    while((!feof(fptr)) && i < size){
        j = 0;
        fgets(buffer, 200, fptr);

        char *token = strtok(buffer, ",");
        char *dateTok;

        strcpy((array + i)->account_number, token);
        while(token != NULL){
            switch(j) {
            case 1:
                strcpy((array + i)->username, token);
                break;

            case 2:
                strcpy((array + i)->email_address, token);
                break;

            case 3:
                (array + i)->balance = strtod(token, NULL);
                break;

            case 4:
                strcpy((array + i)->mobile_number, token);
                break;

            case 5:
                dateTok = strtok(token, "-");
                //Convert the read token into integer
                (array + i)->dateOpened.month = atoi(dateTok);
                while (dateTok != NULL){
                    (array + i)->dateOpened.year = atoi(dateTok);
                    dateTok = strtok(NULL, "-");
                }
                break;
            }
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    acCount = i;
}

//This function is main caller for all the other functions in the program
//Gives you a list of options to choose from and then interprets the entered data
// to known commands like a CLI
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
        printf("%s", "Desired option: ");
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

//Checking the account number errors
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

//Testing that the data is save properly
void printUsertest(Account *user){
    printf("Account number: %s\n", user->account_number);
    printf("Name: %s\n", user->username);
    printf("E-mail : %s\n", user->email_address);
    printf("Balance: %.2lf\n", user->balance);
    printf("Mobile: %s\n", user->mobile_number);
    printf("Date Opened: %d %d\n", user->dateOpened.month, user->dateOpened.year);
    printf("\n");
}

//Will be mainly used in ADD function
Account *constructAccount(char *mobile, char *accNum, char *name, char *email, double balanceNum, Date *dateOpnd)
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
void destructAccount(Account *acc)
{
    free(acc);
}

char *StrToUpper(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        *(str + i) = toupper(*(str + i));
    return str;
}
