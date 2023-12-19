#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int month,year;
}Date;

typedef struct
{
    char mobile_number[12];
    char account_number[11];
    char username[20];
    char email_address[30];
    double balance;
    Date dateOpened;

}Account;

//Will be mainly used in ADD function
Account *ConstructAccount(char *mobile, char *accNum, char *name, char *email, double balanceNum, Date *dateOpnd){
    //Reserving memory in the heap for new instance
    Account *acc = malloc(sizeof(Account));
    if (acc == NULL){
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
void DestructAccount(Account *acc){
    free(acc);
}

int main() {

}
