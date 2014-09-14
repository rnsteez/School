// Author: Sean Davis
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include "funix.h"
#include "directory.h"

using namespace std;

Funix::Funix() : umask(0), time(0)
{
  currentDirectory = new Directory("/", 0, 0, NULL);
} // init()


Funix::~Funix()
{
  const char *arguments[] = {"cd", ".."};
  Directory *temp;

  temp = currentDirectory->cd(2, arguments);

  while(temp != currentDirectory)
  {
    currentDirectory = temp;
    temp = currentDirectory->cd(2, arguments);
  } // while still moving up directory structure.

  delete currentDirectory;
} // ~Funix()


void Funix::cd( int argCount, const char *arguments[])
{
  currentDirectory = currentDirectory->cd(argCount, arguments);
} // cd()


int Funix::eXit( int argCount, const char *arguments[])
{
  if(argCount == 1) // proper
    return 0;

  cout << "usage: exit\n";
  return 1;
} // eXit()


void Funix::getCommand( char *command)
{
  writePrompt();
  fgets(command, 80, stdin);

  if(strlen(command))
    command[strlen(command) - 1] = '\0';  // eliminate '\n'

  time++;
} // getCommand()


void Funix::ls( int argCount, const char *arguments[])
{
  currentDirectory->ls(argCount, arguments);
} // ls()


void Funix::mkdir( int argCount, const char *arguments[])
{
  currentDirectory->mkdir( argCount, arguments, umask,
    time);
} // mkdir()


int Funix::processCommand( char *command)
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
      case 0 : cd(argCount, arguments); break;
      case 1 : return eXit(argCount, arguments);
      case 2 : ls(argCount, arguments); break;
      case 3 : mkdir(argCount, arguments); break;
      case 4 : setUmask(argCount, arguments); break;
      default : cout << arguments[0] << ": Command not found.\n";
    } // switch()
  } // if there are arguments

  return 1; // not exit
} // processCommand()


void Funix::run()
{
  char command[80];

  getCommand(command);

  while(processCommand(command))
  {
    getCommand(command);
  } // while not an exit
} // run()


void Funix::setUmask( int argCount, const char *arguments[])
{
  short octal;

  if(argCount != 2)
  {
    printf("usage: umask octal\n");
    return;
  } // if incorrect number of arguments

  for(int i = 0; arguments[1][i]; i++)
    if(!isdigit(arguments[1][i]))
    {
      cout << "usage: umask octal\n";
      return;
    } // if argument contains non-digit

      octal = atoi(arguments[1]);

  if(octal < 0 || octal > 7)
  {
    cout << "umask: octal must be between 0 and 7\n";
    return;
  } // if octal invalid

  umask = atoi(arguments[1]);
} // setUmask()


void Funix::writePrompt()
{
  currentDirectory->showPath();
  cout << " # ";
} // writePrompt()
