#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define sizeUsers 50

void  Menu(void);
char *StrToUpper(char *str);
int   checkAccountNo(char *accStr);
int   checkEmail(char *email);
int   checkName(char *name);
int   checkNumber(char *number);
void  Save(void);
char *convertMonth(int monthnum);
void  advSearch(void);

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

void constructAccount(Account *acc, char *mobile, char *accNum, char *name, char *email, double balanceNum, Date *dateOpnd);
void destructAccount(Account *acc);
void retrieveData(void);
void printUser(const Account *user);

//used throughout the program to calculate available places in the accounts array
unsigned int acCount = 0;

//Array of structs that carries the data of all the users
Account accounts[sizeUsers];

int main()
{
    //1st Step in our code is retrieving all the data saved in the accounts.txt file
    //and collecting it into an array of objects
    retrieveData();

    //Testing the collected data
    for (size_t i = 0; i < 5; i++){
        printUser(accounts + i);
    }

    //Date datee;
    //datee.month = 5;
    //datee.year = 2000;

    //constructAccount(&accounts[2], "01125789654", "9999999999", "Amin", "Nice123@gmail.com", 12346.656, &datee);
    //Save();
    Menu();
    return 0;
}

//Search the user names using strstr function
//Sets the upper case as a reference to avoid case sensitivity
void advSearch(void){
    char search_key[20];
    char buffer[20];
    char choice = 'y';

    do {
        printf("%s", "Enter the search keyword: ");
        gets(search_key);

        int found = 0;

        printf("%s", "Search results:\n\n");
        for (size_t i = 0; i < 5; i++){
            strcpy(buffer, (accounts + i)->username);
            if (strstr(StrToUpper(buffer), StrToUpper(search_key)) != NULL){
                printUser((accounts + i));
                found = 1;
            }
        }

        if (found == 0){
            printf("No matches are found!\n");
        }
        printf("Do you want to search for something else?(Y/N): ");
        scanf("%c", &choice);
        getchar();
    } while (choice == 'y' || choice == 'Y');
}

//Retrieving data from the text file and constructing the instances based on data collected
void retrieveData(void){
    FILE *fptr = fopen("accounts.txt", "r");
    if (fptr == NULL){
        printf("Couldn't find database file!\n");
        exit(-1);
    }

    char buffer[200];
    size_t i = 0, j;

    while((!feof(fptr)) && i < sizeUsers){
        j = 0;
        fgets(buffer, 200, fptr);

        char *token = strtok(buffer, ",");
        char *dateTok;

        strcpy((accounts + i)->account_number, token);
        while(token != NULL){
            switch(j) {
            case 1:
                strcpy((accounts + i)->username, token);
                break;

            case 2:
                strcpy((accounts + i)->email_address, token);
                break;

            case 3:
                (accounts + i)->balance = strtod(token, NULL);
                break;

            case 4:
                strcpy((accounts + i)->mobile_number, token);
                break;

            case 5:
                dateTok = strtok(token, "-");
                //Convert the read token into integer
                (accounts + i)->dateOpened.month = atoi(dateTok);
                while (dateTok != NULL){
                    (accounts + i)->dateOpened.year = atoi(dateTok);
                    dateTok = strtok(NULL, "-");
                }
                break;
            }
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose(fptr);
    acCount = i;
}

//This function is main caller for all the other functions in the program
//Gives you a list of options to choose from and then interprets the entered data
// to known commands like a CLI
void Menu(void)
{
    char choice[20];
    int flag;
    do
    {
        flag = 0;
        printf("%s", "\t******** Main Menu (0o0) ********\n");
        printf("%s", "Please select one of the following options(Enter the EXACT name of desired option):\n");
        printf("%s", " - ADD\n - DELETE\n - MODIFY\n - SEARCH\n - ADVANCED SEARCH\n - WITHDRAW\n");
        printf("%s", " - DEPOSIT\n - TRANSFER\n - REPORT\n - PRINT\n - QUIT\n");
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
            advSearch();

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
            flag = 1;
        }
    }
    while (!flag);
}

//This function sends all the data collected in the program to the database again
//Data is saved in the format account number, user name, email, balance, mobile number, date opened
void Save(void){
    char choice;
    printf("Do you want to save changes?(Y for Yes/N for No): ");
    scanf("%c", &choice);
    if (choice == 'y' || choice == 'Y'){
        FILE *fptr = fopen("accounts.txt", "w");

        for (size_t i = 0; i < 3; i++){
            fprintf(fptr, "%s,", accounts[i].account_number);
            fprintf(fptr, "%s,", accounts[i].username);
            fprintf(fptr, "%s,", accounts[i].email_address);
            fprintf(fptr, "%.2lf,", accounts[i].balance);
            fprintf(fptr, "%s,", accounts[i].mobile_number);
            fprintf(fptr, "%d-%d\n", accounts[i].dateOpened.month, accounts[i].dateOpened.year);
        }

        fclose(fptr);
    }
}

//Checking the account number errors
//Returns 1 if the input is valid
//Returns 0 if the input isn't valid
int checkAccountNo(char *accStr)
{
     if (strlen(accStr) != 10){
        printf("Invalid Account Number!(Should be 10-Digits)\n");
        return 0;
     }
    for (size_t i = 0; *(accStr + i) != '\0'; i++)
    {
        if (!(isdigit(*(accStr + i)) == 1)){
            printf("Invalid Account Number!(Should be numbers ONLY)\n");
            return 0;
        }
    }
    return 1;
}

//Checking the name
//Returns 1 if the number is valid
//returns 0 if the number isn't valid
int checkName(char *name){
    for (size_t i = 0; *(name + i) != '\0'; i++){
        if (isdigit(*(name + i))){
            printf("Invalid Name!(Should letters ONLY)\n");
            return 0;
        }
    }
    return 1;
}

//Checking the Email
//Returns 1 if the number is valid
//returns 0 if the number isn't valid
int checkEmail(char *email){
        if (strstr(email, "@gmail.com") != NULL
        || strstr(email, "@outlook.com") != NULL
        || strstr(email, "@yahoo.com") != NULL
        || strstr(email, "@alexu.edu.eg" != NULL)){
            return 1;
        }

        else {
            printf("Invalid Email or Not Supported Platform!\nSupported platforms :@gmail.com, @outlook.com, @alexu.edu.eg\n");
            return 0;
        }
}

//Checking the mobile number
//Returns 1 if the number is valid
//returns 0 if the number isn't valid
int checkNumber(char *number){
    if (strlen(number) != 11){
        printf("Invalid Mobile Number!(Should contain 11 numbers)\n");
        return 0;
    }

    for (size_t i = 0; *(number + i) != '\0'; i++){
        if (isalpha(*(number + i))){
            printf("Invalid Mobile Number!(Shouldn't contain letters)\n");
            return 0;
        }
    }

    return 1;
}

//Testing that the data is saved properly
void printUser(const Account *user){
    printf("Account number: %s\n", user->account_number);
    printf("Name: %s\n", user->username);
    printf("E-mail : %s\n", user->email_address);
    printf("Balance: %.2lf\n", user->balance);
    printf("Mobile: %s\n", user->mobile_number);
    printf("Date Opened: %s %d\n", convertMonth(user->dateOpened.month), user->dateOpened.year);
    printf("\n");
}

//Will be mainly used in ADD function
void constructAccount(Account *acc, char *mobile, char *accNum, char *name, char *email, double balanceNum, Date *dateOpnd)
{
    //Copying the arguments into the new instance arguments
    strcpy(acc->account_number, accNum);
    strcpy(acc->mobile_number, mobile);
    strcpy(acc->email_address, email);
    strcpy(acc->username, name);
    acc->balance = balanceNum;
    acc->dateOpened.month = dateOpnd->month;
    acc->dateOpened.year = dateOpnd->year;
}

//Will be used before closing the program
void destructAccount(Account *acc)
{
    free(acc);
}

//Function that changes all the characters in a string to UPPER case
char *StrToUpper(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        *(str + i) = toupper(*(str + i));
    return str;
}

char *convertMonth(int monthnum){
    switch(monthnum){
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    }
}
