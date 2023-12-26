#include <stdio.h>
#include <stdlib.h>

void report(void)
{
    char account_number[11];
    char fileName[16];
    char buf[100];
    char n;
    int count=0;
    int i;

    do
    {
        printf("%s","enter your account number:");
        gets(account_number);
    }
    while (checkAccountNo(account_number)==0); //acc num invalid
    if(AccountExistenceCheck(account_number)==0)
    {
        sprintf(fileName,"%s.txt",account_number);
        fopen(fileName,"r");
        for(i=0; !feof(fileName); i++)
        {
            n=fgetc(fileName);
            if(n=='\n')
                count++;

        }

        fseek(fileName,0,SEEK_SET);
        if(count<5||count==5)
        {
            for(i=0; i<count; i++)
            {
                fgets(buf,99,fileName);
                printf("%s",buf);
            }
        }
        else
        {
            for(i=0; i<(count-5); i++)
            {
                fgets(buf,99,fileName);

            }
            for(i=0; i<5; i++)
            {
                fgets(buf,99,fileName);
                printf("%s",buf);
            }
        }
        fclose(fileName);
    }
}

