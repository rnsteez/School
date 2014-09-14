//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funix.h"
#include "directory.h"
#include "permissions.h"

void run(Funix *funix)
{
	init(funix);
	char *command = (char*) malloc((sizeof(char))*80);
	int exitTest = 1;
	do 
	{
		getCommand(funix, command);
		funix->time++;
		exitTest = processCommand(funix, command);
	} while (exitTest != 0);
} // reads and processes commands until proper exit

void init(Funix *funix)
{
	funix->currentDirectory = (Directory*) malloc(sizeof(Directory));

	funix->currentDirectory->name = (char*) malloc(sizeof(char)*80);

	funix->currentDirectory->name[0] = '/';

	funix->currentDirectory->time = 0;

	funix->currentDirectory->subD = (Directory**) malloc(MAX_SUBD*sizeof(Directory*));

	funix->currentDirectory->numSubD = 0;

	funix->currentDirectory->parentD = NULL;

    	funix->currentDirectory->dPermissions.per=7;
	funix->umask = 0;
	funix->time = 0;
} // creates currentDirectory, and sets umask and time

void getCommand(Funix *funix, char *command)
{
	writePrompt(funix);
	fgets(command, 80, stdin);
} // writes prompt and reads command

void writePrompt(Funix *funix)
{
	printdir(funix->currentDirectory);
	printf(" # ");
} // shows path and '#'

int eXit(Funix *funix, int argCount, const char *arguments[])
{
	if (argCount != 1)
	{
		printf("usage: exit\n");
		return 1;
	}
	else
		return 0;
} // checks "exit" command, returns 0 on proper exit

int processCommand(Funix *funix, char *command) //MISSION SUCCESS
{
	char atest = 'x';
	char *test = &atest;
	int argCount, i;
	char* temp = (char*) malloc((sizeof(char))*80);
	strcpy(temp,command);
	for (argCount = -1; test != NULL; argCount++)
	{
		if (argCount == -1)
			test = strtok(temp, " \n");
		else
			test = strtok(NULL, " \n");
	}
	const char **arguments = (const char**) malloc((sizeof(char*))*argCount);
	for(i=0; i < argCount; i++)
	{
		*(arguments+i) = (char*) malloc((sizeof(char))*80);
	}
	arguments[0] = strtok(command, " \n");
	for(i=1; i < argCount; i++)
	{
		arguments[i] = strtok(NULL, " \n");
	}
	if (arguments[0] == NULL)
	{
		return 1;
	}
	else if (!strcmp(arguments[0], "cd"))
	{
		cd(funix, argCount, arguments);
		return 1;
	}
	else if (!strcmp(arguments[0], "ls"))
	{
		ls(funix, argCount, arguments);
		return 1;
	}
	else if (!strcmp(arguments[0], "mkdir"))
	{
		mkdir(funix, argCount, arguments);
		return 1;
	}
	else if (!strcmp(arguments[0], "umask"))
	{
		umask(funix, argCount, arguments);
		return 1;
	}
	else if (!strcmp(arguments[0], "exit"))
	{
		return (eXit(funix, argCount, arguments));
	}
	else
	{
		printf("%s: Command not found.\n", arguments[0]);
		return 1;
	}
} // returns 0 on proper exit
