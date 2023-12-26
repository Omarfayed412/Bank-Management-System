#include <stdio.h>
#include <stdlib.h>
void Transfer(void)
{
    char account_number1[11];
    char account_number2[11];
    char amount1[sizeof(double)];
    double amount2;
    char choicee;
    char fileName1[16];
    char fileName2[16];
    int flag=0;
    int flag2=0;

    do
    {
        do
        {
            printf("%s", "Enter Sender account number:");
            gets(account_number1);
        }
        while (checkAccountNo(account_number1)==0); //acc num invalid

        do
        {
            printf("%s","Enter Receiver account number:");
            gets(account_number2);
            if(strcmp(account_number1,account_number2)==0)
            {
              printf("Enter different reciever account");
              flag2=1;
            }

        }
        while (checkAccountNo(account_number2) == 0 && flag2==1);  //acc num invalid

        if(AccountExistenceCheck(account_number1) == 0 && AccountExistenceCheck(account_number2) == 0)//acc 1,2 are exist
        {
            int index1 = loadAccIndex(account_number1);
            int index2 = loadAccIndex(account_number2);

            do
            {
                do
                {
                printf("%s", "Enter an amount to transfer: ");
                gets(amount1);


                }while(checkBalance(amount1)==0);
                amount2=strtod(amount1,NULL);


                if(amount2 > accounts[index1].balance)
                {
                    printf("You only have %lf$ in your account\n", accounts[index1].balance);
                    flag = 1;
                    break;
                }
            }
            while(amount2 < 0);

            if(flag == 0)
            {
                accounts[index1].balance -= amount2;
                accounts[index2].balance += amount2;
                sprintf(fileName1, "%s.txt", accounts[index1].account_number);
                sprintf(fileName2, "%s.txt", accounts[index2].account_number);
                accounts[index1].f_report = fopen(fileName1, "a");
                if(accounts[index1].f_report == NULL)
                {
                    printf("Couldn't Find File!\n");
                    exit(-1);
                }

                fprintf(accounts[index1].f_report, "You sent %lf$ to %s", amount2, account_number2);
                fclose(accounts[index1].f_report);

                accounts[index2].f_report = fopen(fileName2, "a");
                if(accounts[index2].f_report == NULL)
                {
                    printf("Couldn't Find File!\n");
                    exit(-1);
                }
                fprintf(accounts[index2].f_report, "You received %lf$ from %s", amount2, account_number2);
                fclose(accounts[index2].f_report);

                Save();
                printf("Transaction Successful :)\n");

            }
            else
                printf("Transaction Failed!\n");
        }
        printf("\nDo you want to Transfer again?(Y/N): ");
        scanf("%c", &choicee);
        getchar();
    }
    while (choicee == 'y' || choicee == 'Y');
}
