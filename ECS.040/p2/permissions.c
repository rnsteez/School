//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."
// The cake is a lie!

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "permissions.h"
#include "funix.h"

void printper(Permissions *permissions)
{
	if (permissions->per>3)
    		printf("r");
	else
    		printf("-");
	if (permissions->per==2||permissions->per==3||permissions->per==6||permissions->per==7)
    		printf("w");
	else
    		printf("-");
	if (permissions->per%2==1)
    		printf("x");
	else
		printf("-");
}

void umask(Funix *funix, int argCount, const char *arguments[])
{

	if (argCount == 2)
	{
		int i, b = strlen(arguments[1]);
		for (i = 0; i < b; i++)
		{
	        	if (isdigit(arguments[1][i]) == 0)
			{
				printf("usage: umask octal\n");
				return;
			}
		}
		int numz = atoi(arguments[1]);
		if (numz<8 && numz>-1)
               		funix->umask=numz;
            	else
               		printf("umask: octal must be between 0 and 7\n");
	}
	else
		printf("usage: umask octal\n");
}
