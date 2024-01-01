#include <stdio.h>
#include <stdlib.h>
#include "BankSystem.h"

int main()
{
    printf("======================\nBank Management System\n======================\n");
    Login();

    loadAccounts();


    ///1st Step in our code is retrieving all the data saved in the accounts.txt file
    ///and collecting it into an array of objects
    //retrieveData();

    //Testing the collected data
   for (size_t i = 0; i < acCount; i++)
    {
        printUser(accounts + i);
    }

    Menu();
    return 0;
}
