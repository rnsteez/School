//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
#include "funix.h"
#include "directory.h"

using namespace std;

Funix::Funix()
{
  ifstream is;
  is.open("directories.txt");
  if (is.good())
    is >> *this;
  is.close();
  umask.chmod(22);
  if (!currentDirectory)
    currentDirectory = new Directory("/", umask, NULL);
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

  ofstream os;
  os.open("directories.txt", ios_base::trunc);
  os << *this;
  os.close();
  
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

} // getCommand()


void Funix::ls( int argCount, const char *arguments[])
{
  currentDirectory->ls(argCount, arguments);
} // ls()


void Funix::mkdir( int argCount, const char *arguments[])
{
  currentDirectory->mkdir( argCount, arguments, umask);
} // mkdir()


int Funix::processCommand( char *command)
{
  static const char *commands[] = {"cd", "exit", "ls", "mkdir", "umask", "chmod", "cp"};
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
    for(commandNum = 0; commandNum < 7; commandNum++)
      if(!strcmp(arguments[0], commands[commandNum]))
        break;

    switch(commandNum)
    {
      case 0 : cd(argCount, arguments); break;
      case 1 : return eXit(argCount, arguments);
      case 2 : ls(argCount, arguments); break;
      case 3 : mkdir(argCount, arguments); break;
      case 4 : setUmask(argCount, arguments); break;
      case 5 : currentDirectory->chmod(argCount, arguments); break;
      case 6 : currentDirectory->cp(argCount, arguments); break;
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
  short test[3];

  if(argCount < 2)
  {
    cout << "usage: umask octal\n";
    return;
  } // if incorrect number of arguments

  for(int i = 0; arguments[1][i]; i++)
    if(!isdigit(arguments[1][i]))
    {
      cout << "usage: umask octal\n";
      return;
    } // if argument contains non-digit

  if (strlen(arguments[1]) > 3)
  {
    for(int i = 0; arguments[1][i] < (int) strlen(arguments[1]) - 3; i++)
    if(arguments[1][i] != 0)
    {
      cout << "umask: octal must be between 0 and 777\n";
      return;
    }
  } // if there is any number except 0 before last 3 digits
  
  for(int i = 0; arguments[1][i]; i++)
      test[i] = arguments[1][i] - '0';
  
  for(int i = 0; arguments[1][i]; i++)
  {
  if(test[i] < 0 || test[i] > 7)
    {
      cout << "umask: octal must be between 0 and 777\n";
      return;
    } // if octal invalid
  }
  
  umask.chmod(atoi(arguments[1]));
  
} // setUmask()




void Funix::writePrompt()
{
  currentDirectory->showPath();
  cout << " # ";
} // writePrompt()

ofstream& operator<<(ofstream& os, const Funix &funix)
{
  os << *(funix.currentDirectory);
  return os;
}

ifstream& operator>>(ifstream& is, Funix &funix)
{
  is >> &(funix.currentDirectory);
  return is;
}