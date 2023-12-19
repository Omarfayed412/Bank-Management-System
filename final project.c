// C Program to illustrate file opening
#include <stdio.h>
#include <stdlib.h>

int main()
{
	// file pointer variable to store the value returned by
	// fopen
	FILE* fptr;
    char std[1000];
	// opening the file in read mode
	fptr = fopen("accounts.txt", "r");

	// checking if the file is opened successfully
	if (fptr == NULL) {
		printf("The file is not opened. The program will "
			"now exit.");
		exit(0);
	}
	int a;
	fscanf(fptr,"%d",&a);
	printf("%d",a);

	return 0;
}
