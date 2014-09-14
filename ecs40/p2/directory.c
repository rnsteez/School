//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."
// The cake is a lie!

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "directory.h"
#include "permissions.h"
#include "funix.h"

void ls(Funix *funix, int argCount, const char *arguments[])
{
	if (argCount > 2)
	{
		printf("usage: ls [-l]\n");
	}
	else
	{
		if (argCount == 2)
		{
			if (strcmp(arguments[1],"-l"))
				printf("usage: ls [-l]\n");
			else
			{
				int i;
				for  (i = 0; i < funix->currentDirectory->numSubD; i++)
				{
					printper(&(funix->currentDirectory->subD[i]->dPermissions));
					printf(" %d",funix->currentDirectory->subD[i]->time);
					printf(" %s\n",funix->currentDirectory->subD[i]->name);
				}
			}
		}
		else
		{
			int i;
			for  (i = 0; i < funix->currentDirectory->numSubD; i++)
			{
				printf("%s\n",funix->currentDirectory->subD[i]->name);
			}
		}
	}
	funix->time++;
}  // calls ls() with currentDirectory as one of its parameters

void mkdir(Funix *funix, int argCount, const char *arguments[])
{
	if (argCount != 2)
	{
		printf("usage: mkdir directory_name\n");
	}
	else if (funix->currentDirectory->numSubD+1 > MAX_SUBD)
	{
		printf("mkdir: %s already contains the maximum number of directories\n", funix->currentDirectory->name);
	}
	else
	{
		int i;
		int test = 1;
		for (i = 0; i < funix->currentDirectory->numSubD; i++)
		{
			if (!strcmp(arguments[1], funix->currentDirectory->subD[i]->name))
       			{
            			printf("mkdir: cannot create directory ‘%s’: File exists\n", arguments[1]);
				test = 0;
           			break;
        		}
		}
		if (test == 1)
		{
			funix->currentDirectory->subD[funix->currentDirectory->numSubD] = (Directory*) malloc(sizeof(Directory));
			
			funix->currentDirectory->subD[funix->currentDirectory->numSubD]->name = (char*) malloc(sizeof(char));

			strcpy(funix->currentDirectory->subD[funix->currentDirectory->numSubD]->name,arguments[1]);

			funix->currentDirectory->subD[funix->currentDirectory->numSubD]->time = funix->time;

			funix->currentDirectory->subD[funix->currentDirectory->numSubD]->subD = (Directory**) malloc(MAX_SUBD*sizeof(Directory*));

			funix->currentDirectory->subD[funix->currentDirectory->numSubD]->numSubD = 0;

			funix->currentDirectory->subD[funix->currentDirectory->numSubD]->parentD = funix->currentDirectory;

    			funix->currentDirectory->subD[funix->currentDirectory->numSubD]->dPermissions.per=7;

    			if (funix->umask>3)
        			funix->currentDirectory->subD[funix->currentDirectory->numSubD]->dPermissions.per -= 4;
			if (funix->umask==2||funix->umask==3||funix->umask==6||funix->umask==7)
        			funix->currentDirectory->subD[funix->currentDirectory->numSubD]->dPermissions.per -= 2;
    			if (funix->umask%2==1)
        			funix->currentDirectory->subD[funix->currentDirectory->numSubD]->dPermissions.per -= 1;

			funix->currentDirectory->numSubD++;
		}
    	}
		
}  // calls mkdir() with currentDirectory as one of its parameters

void cd(Funix *funix, int argCount, const char *arguments[])
{
	if (argCount != 2)
		printf("usage: cd directoryName\n");
	else
	{
		int i;
		int index = -1;
		for (i = 0; i < funix->currentDirectory->numSubD; i++)
		{
			if (!strcmp(arguments[1],funix->currentDirectory->subD[i]->name))
				index = i;
		}
		if (!strcmp(arguments[1], ".."))
			if (funix->currentDirectory->parentD == NULL)
				funix->currentDirectory = funix->currentDirectory;
			else
				funix->currentDirectory = funix->currentDirectory->parentD;
		else if (index == -1)
			printf("%s: no such directory\n", arguments[1]);
		else //might have problems here
		{
			funix->currentDirectory = funix->currentDirectory->subD[index];
		}
	}
}  // calls cd() with currentDirectory as one of its parameters

void printdir(Directory *currentDirectory)
{
	if (currentDirectory->parentD == NULL)
	{
		printf("/");
		return;
	}
	else
	{
		printdir(currentDirectory->parentD);
		printf("%s/",currentDirectory->name);
	}
} //recursively prints the current directory
