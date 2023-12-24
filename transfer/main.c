#include <stdio.h>
#include <stdlib.h>
void Transfer(void)
{
    char account_number1[11];
    char account_number2[11];
    int amount;
    char choice;
    char fileName1[16];
    char fileName2[16];
    int flag=0;

    do
    {
        do
        {
            printf("%s","enter sender account number:");
            gets(account_number1);

        }
        while (checkAccountNo(account_number1)==0); //acc num invalid
        do
        {
            printf("%s","enter receiver account number:");
            gets(account_number2);

        }
        while (checkAccountNo(account_number2)==0);  //acc num invalid
        if(AccountExistenceCheck(account_number1)==0&&AccountExistenceCheck(account_number2)==0)//acc 1,2 are exist
        {
            int index1=loadAccIndex(account_number1);
            int index2=loadAccIndex(account_number2;

             do
            {
                printf("%s","enter an amount to transfer: ");
                scanf("%d",&amount);
                if(amount>accounts[index1].balance)
                {
                    printf("you only have %lf$ in your account",accounts[index1].balance);
                    flag=1;
                    break;

                }


            }
            while(amount <0);
            if(flag==0)
            {
                    accounts[index1].balance-=amount;
                    accounts[index2].balance+=amount;
                    sprintf(fileName1,"%s.txt",accounts[index1].account_number);
                    sprintf(fileName2,"%s.txt",accounts[index2].account_number);
                    accounts[index1].f_report=fopen(fileName1,"a");
                    if(accounts[index1].f_report==NULL)
                    {
                        printf("Couldn't find file!\n");
                        exit(-1);
                    }
                    fprintf(accounts[index1].f_report,"you sent %d$ to %s",amount,account_number2);
                    fclose(accounts[index1].f_report);

                    accounts[index2].f_report=fopen(fileName2,"a");
                    if(accounts[index2].f_report==NULL)
                    {
                        printf("Couldn't find file!\n");
                        exit(-1);
                    }
                    fprintf(accounts[index2].f_report,"you received %d$ from %s",amount,account_number2);
                    fclose(accounts[index2].f_report);
                    save();
                    printf("transaction successful");

                    }
                    else
                    printf("transaction failed");


             }

        printf("Do you want to Withdraw again?(Y/N): ");
        scanf("%c", &choice);

    }
    while (choice=='y'||choice=='Y');

}

