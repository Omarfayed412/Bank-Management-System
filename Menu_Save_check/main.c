#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void Menu(void);
char *StrToUpper(char *str);

int main()
{
    Menu();
    return 0;
}

void Menu(void){
    char choice[20];
    int flag;

    printf("%s", "Please select one of the following options(Enter the EXACT name of desired option):\n");
    printf("%s", " - ADD\n - DELETE\n - MODIFY\n - SEARCH\n - ADVANCED SEARCH\n - WITHDRAW\n");
    printf("%s", " - DEPOSIT\n - TRANSFER\n - REPORT\n - PRINT\n - QUIT\n");



    do {
        flag = 1;
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

        else{
            printf("%s", "Invalid option entered!\n");
            flag = 0;
        }
    } while (!flag);
}

char *StrToUpper(char *str){
    for (size_t i = 0; str[i] != '\0'; i++)
        *(str + i) = toupper(*(str + i));
    return str;
}
