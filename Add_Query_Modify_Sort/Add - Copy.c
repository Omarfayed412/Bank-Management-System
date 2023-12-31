#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define sizeUsers 50
#include <ctype.h>

/// total number of clients already in the system
int accountsNumbers=1;

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

} Account;

Account client[sizeUsers];
void Modify();
void *ConstructAccount(Account *acc,char *mobile, char *accNum, char *name, char *email, double *balanceNum, Date *dateOpnd);
char *convertMonth(int monthnum);
void Add();
int checkAccountNo(char *accStr);
void Query();
int checkNumber(char *number);
int checkEmail(char *email);
int AccountExistenceCheck (char *accountNumber);
int checkName(char *name);
int loadAccIndex(char *accountNumber);

void main()
{
    strcpy(client[0].account_number,"1234567891");
    strcpy(client[0].email_address,"yi@gmail.com");
    strcpy(client[0].mobile_number,"01143931945");
    strcpy(client[0].username,"Omar");
    client[0].balance=223;
    client[0].dateOpened.month=12;
    client[0].dateOpened.year=2020;


    char c;
    client[0].balance=223;
    strcpy(client[1].account_number,"1234567892");
    do
    {
        scanf("%c",&c);
        getchar();
        if(c=='a')
        {
            Add();
        }
        else if(c=='q')
        {
            Query();
        }
        else
        {
            Modify();
        }
    }
    while(1);
}
void Save(void)
{
    char choice;
    printf("Do you want to save changes?(Y for Yes/N for No): ");
    scanf("%c", &choice);
    getchar();
    if (choice == 'y' || choice == 'Y')
    {
        FILE *fptr = fopen("accounts.txt", "w");

        for (size_t i = 0; i < accountsNumbers; i++)
        {
            fprintf(fptr, "%s,", client[i].account_number);
            fprintf(fptr, "%s,", client[i].username);
            fprintf(fptr, "%s,", client[i].email_address);
            fprintf(fptr, "%.2lf,", client[i].balance);
            fprintf(fptr, "%s,", client[i].mobile_number);
            fprintf(fptr, "%d-%d\n", client[i].dateOpened.month, client[i].dateOpened.year);
        }

        fclose(fptr);
    }
}
void *ConstructAccount(Account *acc,char *mobile, char *accNum, char *name, char *email, double *balanceNum, Date *dateOpnd)
{
    //Copying the arguments into the new client data
    strcpy(client[accountsNumbers].account_number, accNum);
    strcpy(client[accountsNumbers].mobile_number, mobile);
    strcpy(client[accountsNumbers].email_address, email);
    strcpy(client[accountsNumbers].username, name);
    client[accountsNumbers].balance = *balanceNum;
    client[accountsNumbers].dateOpened.month = dateOpnd->month;
    client[accountsNumbers].dateOpened.year = dateOpnd->year;

}

char *StrToUpper(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        *(str + i) = toupper(*(str + i));
    return str;
}

void Query()
{

    char reqAcc[11];
    int flag=0;
    char choise;
    printf("%s\n","----  Search for an Account ---");
    do
    {
        printf("%s\n","Please enter the account number :");
        do
        {
            gets(reqAcc);
            flag=checkAccountNo(reqAcc);
        }
        while(flag==0);
        /// deal with the situation of non existing accounts
        if(AccountExistenceCheck(reqAcc)!=0)
        {
            printf("This account don't exist !!\n");
            printf("%s","[Y] to Add a new account  or [N] to go the Menu : ");
            scanf("%c",&choise);
            getchar();
            if(choise=='Y'||choise=='y')
            {
                Add();
                choise='n';
            }
            else
            {
                break;
            }
        }
        /// load the details of the required account
        else
        {
            /// search for the index of the required account in the main structure of the clients
            int place=loadAccIndex(reqAcc);
            printf("\n%s: %s\n","Account Number",client[place].account_number);
            printf("%s: %s\n","Name",client[place].username);
            printf("%s: %s\n","E-mail",client[place].email_address);
            printf("%s: %s\n","Mobile",client[place].mobile_number);
            printf("%s: %s %d\n ","Data Opened",convertMonth(client[place].dateOpened.month),client[place].dateOpened.year);
            printf("Do you want to search for more accounts?(Y for Yes/N for No): ");
            scanf("%c", &choise);
            getchar();
        }

    }
    while((choise== 'y' || choise== 'Y'));
}

/// check the account number
int checkAccountNo(char *accStr)
{
    if (strlen(accStr) != 10)
    {
        printf("Invalid Account Number!(Should be 10-Digits)\n");
        return 0;
    }
    for (size_t i = 0; *(accStr + i) != '\0'; i++)
    {
        if (!(isdigit(*(accStr + i)) == 1))
        {
            printf("Invalid Account Number!(Should be numbers ONLY)\n");
            return 0;
        }
    }
    return 1;
}

///Checking the name
///Returns 1 if the number is valid
///returns 0 if the number isn't valid
int checkName(char *name)
{
    for (size_t i = 0; *(name + i) != '\0'; i++)
    {
        if (isdigit(*(name + i)))
        {
            printf("Invalid Name!(Should letters ONLY)\n");
            return 0;
        }
    }
    return 1;
}

///Checking the Email
///Returns 1 if the number is valid
///returns 0 if the number isn't valid
int checkEmail(char *email)
{
    if (strstr(email, "@gmail.com") != NULL
            || strstr(email, "@outlook.com") != NULL
            || strstr(email, "@yahoo.com") != NULL
            || strstr(email, "@alexu.edu.eg" != NULL))
    {
        return 1;
    }

    else
    {
        printf("Invalid Email or Not Supported Platform!\nSupported platforms :@gmail.com, @outlook.com, @alexu.edu.eg\n");
        return 0;
    }
}

///Checking the mobile number
///Returns 1 if the number is valid
///returns 0 if the number isn't valid
int checkNumber(char *number)
{
    if (strlen(number) != 11)
    {
        printf("Invalid Mobile Number!(Should contain 11 numbers)\n");
        return 0;
    }

    for (size_t i = 0; *(number + i) != '\0'; i++)
    {
        if (isalpha(*(number + i)))
        {
            printf("Invalid Mobile Number!(Shouldn't contain letters)\n");
            return 0;
        }
    }

    return 1;
}

/// return the index of the required client
int loadAccIndex(char *accountNumber)
{

    int counter=0;
    for(counter; counter<accountsNumbers; ++counter)
    {
        if(strcmp(accountNumber,client[counter].account_number)==0)
            return counter;
    }

}

///return 0 if the account already exist
///return 1 if the account do not exist
/// check existence of an account number
int AccountExistenceCheck (char *accountNumber)
{
/// Add new account
    int counter,flag=0;
    for(counter=0; counter<accountsNumbers; ++counter)
    {
        flag=strcmp(accountNumber,client[counter].account_number);

        if(flag==0)
        {
            return flag;
        }
    }
    return flag;
}

void Add()
{

/// return a pointer to the current calendar time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char account_number[11];
    char mobile_number[12];
    char username[20];
    char choice_2;
    int flag_1=0,flag_2=0;
    char email_adresss[30];
    double balance=0;
    Date data;

    do
    {
        /// print the number of available places
        printf("There are a %d places allowed\n",sizeUsers-accountsNumbers);
        printf("%s\n","----  New Account ---");
        do
        {
            printf("%s","Account_number : ");

            gets(account_number);

            flag_1=checkAccountNo(account_number);
            if (flag_1==0)
            {
                continue;
            }
            flag_2=AccountExistenceCheck(account_number);
            if(flag_2==0)
            {
                printf("%s\n","Account already exist!!\n");
            }

        }
        while(flag_1==0||flag_2==0);
        do
        {
            printf("%s","UserName: ");
            gets(username);
            flag_1=0;
            flag_1=checkName(username);
        }
        while(flag_1==0);
        do
        {
            flag_1==0;
            printf("%s","Mobile Number: ");
            gets(mobile_number);
            flag_1=checkNumber(mobile_number);
        }
        while(flag_1==0);

        do
        {
            flag_1=0;
            printf("%s","Email Adresss: ");
            gets(email_adresss);
            flag_1=checkEmail(email_adresss);
        }
        while(flag_1==0);
/// the data of adding the account
        data.year=tm.tm_year+1900;
        data.month=tm.tm_mon+1;
/// making an instant of the data
        Account *new_client=malloc(sizeof(Account));
        ConstructAccount(new_client,mobile_number,account_number,username,email_adresss,&balance,&data);
/// increasing the number of accounts
        ++accountsNumbers;
        Save();
        printf("%s\n","Account added successfully!!");
///choice for adding ,more accounts
        printf("Do you want to add more accounts?(Y for Yes/N for No): ");
        scanf("%c", &choice_2);
        getchar();
    }
    while((choice_2== 'y' || choice_2== 'Y'));
}
void Modify()
{
    char accReqMod[11];
    char choice = 'y';
    do
    {
        printf("%s\n","----  Modify Account ---\n");
        /// check for account length limit
        do
        {
            printf("Enter account number needed to modify: ");
            gets(accReqMod);

        }
        while(checkAccountNo(accReqMod)==0);
        /// in case of account do not exist
        if(AccountExistenceCheck(accReqMod)!=0)
        {
            printf("This account don't exist !!\n");
            printf("%s","[Y] to Add a new account  or [N] to go the Menu : ");
            scanf("%c",&choice);
            getchar();
            if(choice=='Y'||choice=='y')
            {
                Add();
                choice='n';
            }
        }
        /// modify the required account
        else
        {
            int place=loadAccIndex(accReqMod);
            char choice;
            printf("Do you want to add on (N for Number,U for Username,E for E-mail: ");
            scanf("%c",&choice);
            getchar();
            if(choice=='U'||choice=='u')
            {
                do
                {

                    printf("Name: ");
                    gets(client[place].username);
                    ///check if the user entered the same old email

                }
                while(checkName(client[place].username)==0);
            }
            else if (choice=='n'||choice=='N')
            {
                do
                {

                    printf("Mobile Number: ");
                    gets(client[place].mobile_number);
                    ///check if the user entered the same old number
                }
                while(checkNumber(client[place].mobile_number)==0);
            }
            else if(choice=='e'||choice=='E')
            {
                do
                {

                    printf("E_mail: ");
                    gets(client[place].email_address);
                }
                while(checkEmail(client[place].email_address)==0);
            }

            /// if the user entered neither of the choices
            else
            {
                printf("invalid choice");
            }
        }

        Save();
        printf("\nDo want to modify again?!!\n(Y for yes, N for no)");
        scanf("%c",&choice);
        getchar();
        getchar();
    }
    while(choice=='y'||choice=='y');
}
char *convertMonth(int monthnum)
{

    switch(monthnum)
    {
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
