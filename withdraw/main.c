#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void WithDraw (void)
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
            int index=loadAccIndex(account_number);
            printf("your balance= %lf$",accounts[index].balance);
            do
            {
                printf("%s","enter an amount to withdraw(Max limit=10,000$/transaction): ");
                scanf("%d",&amount);
            }
            while(amount>10000|| amount>accounts[index].balance||amount <0);
            accounts[index].balance-=amount;

            sprintf(fileName, "%s.txt", accounts[index].account_number);
            accounts[index].f_report=fopen(fileName,"a");
            if (accounts[index].f_report==NULL)
            {
                printf("Couldn't find file!\n");
                exit(-1);
            }
            fprintf(accounts[index].f_report,"withdraw %d$\n",amount);
            fclose(accounts[index].f_report);
            save();
            printf("transaction successful");

        }
        else
            printf("transaction failed");

        printf("Do you want to Withdraw again?(Y/N): ");
        scanf("%c", &choice);
        getchar();



    }
    while (choice=='y'||choice=='Y');


