#include <stdio.h>
#include <stdlib.h>

void Deposit (void)
{
    char account_number[11];
    int amount;
    char choice;
    char fileName[16];
    do
    {
        do
        {
            printf("%s","enter your account number:");
            gets(account_number);


        }
        while (checkAccountNo(account_number)==0); //acc num invalid

        if(AccountExistenceCheck(account_number)==0)//acc exist
        {
            do
            {
                printf("%s","enter the amount needs to be deposited (Max limit=10000$): ");
                scanf("%d",&amount);
            }
            while(amount>10000);
            int index=loadAccIndex(account_number);
            accounts[index].balance+=amount;
            sprintf(fileName,"%s.txt",accounts[index].accountnumber);
            accounts[index].f_report=fopen(fileName,"a");
            if (accounts[index].f_report==NULL)
                {
                    printf("Couldn't find file!\n");
                    exit(-1);
                }
            fprintf(accounts[index].f_report,"Deposit %d$\n",amount);
            fclose(accounts[index].f_report);
            save();
            printf("transaction successful");

        }
        else
            printf("transaction failed");

        printf("Do you want to deposit again?(Y/N): ");
        scanf("%c", &choice);
        getchar();



    }
    while (choice=='y'||choice=='Y');



