// Author: Sean Davis
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funix.h"
#include "directory.h"


void cd(Funix *funix, int argCount, const char *arguments[])
{
  funix->currentDirectory = cd(funix->currentDirectory, argCount, arguments);
} // cd()


int eXit(Funix *funix, int argCount, const char *arguments[])
{
  if(argCount == 1) // proper
    return 0;

  printf ("usage: exit\n");
  return 1;
} // eXit()


void getCommand(Funix *funix, char *command)
{
  writePrompt(funix);
  fgets(command, 80, stdin);

  if(strlen(command))
    command[strlen(command) - 1] = '\0';  // eliminate '\n'
    
  funix->time++;
} // getCommand()


void init(Funix *funix)
{
  funix->umask = 0;
  funix->time = 0;
  funix->currentDirectory = (Directory*) malloc(sizeof(Directory));
  createDirectory(funix->currentDirectory, "/", 0, 0, NULL);
} // init()


void ls(Funix *funix, int argCount, const char *arguments[])
{
  ls(funix->currentDirectory, argCount, arguments);
} // ls()


void mkdir(Funix *funix, int argCount, const char *arguments[])
{
  mkdir(funix->currentDirectory, argCount, arguments, funix->umask,
    funix->time);
} // mkdir()


int processCommand(Funix *funix, char *command)
{
  static const char *commands[] = {"cd", "exit", "ls", "mkdir", "umask"};
  char *ptr;
  const char* arguments[40];
  int commandNum, argCount = 0;
  ptr = strtok(command, " \n");

  while(ptr)
  {
    arguments[argCount++] = ptr;
    ptr = strtok(NULL, " \n");
  } // while more arguments in command

  if(argCount > 0)
  {
    for(commandNum = 0; commandNum < 5; commandNum++)
      if(!strcmp(arguments[0], commands[commandNum]))
        break;

    switch(commandNum)
    {
      case 0 : cd(funix, argCount, arguments); break;
      case 1 : return eXit(funix, argCount, arguments);
      case 2 : ls(funix, argCount, arguments); break;
      case 3 : mkdir(funix, argCount, arguments); break;
      case 4 : umask(funix, argCount, arguments); break;
      default : printf("%s: Command not found.\n", arguments[0]);
    } // switch on command number
  } // if there are arguments

  return 1; // not exit
} // processCommand()


void run(Funix *funix)
{
  char command[80];
  init(funix);
  getCommand(funix, command);

  while(processCommand(funix, command))
  {
    getCommand(funix, command);
  } // while not an exit
} // run()


void umask(Funix *funix, int argCount, const char *arguments[])
{
  int octal;

  if(argCount != 2)
  {
    printf("usage: umask octal\n");
    return;
  } // if not two arguments

  for(int i = 0; arguments[1][i]; i++)
    if(!isdigit(arguments[1][i]))
    {
      printf("usage: umask octal\n");
      return;
    } // if is digit

  octal = atoi(arguments[1]);

  if(octal < 0 || octal > 7)
  {
    printf("umask: octal must be between 0 and 7\n");
    return;
  } // if octal invalid

  funix->umask = octal;
} // umask()


void writePrompt(Funix *funix)
{
  showPath(funix->currentDirectory);
  printf(" # ");
} // writePrompt()
