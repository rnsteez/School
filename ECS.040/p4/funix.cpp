// Author: Sean Davis
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
#include "funix.h"
#include "directory.h"

using namespace std;

Funix::Funix()
{
  currentDirectory = new Directory("/", 022, NULL);
  ifstream inf("directories.txt");

  if(inf)
    inf >> *this;
  else
    umask = 022;
} // Funix()


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


void Funix::chmod( int argCount, const char *arguments[])
{
  currentDirectory->chmod(argCount, arguments);
} // chmod()


void Funix::cp( int argCount, const char *arguments[])
{
  currentDirectory->cp(argCount, arguments);
} // cp()


int Funix::eXit( int argCount, const char *arguments[])
{
  const char *args[] = {"cd", ".."};

  if(argCount == 1) // proper
  {
    Directory *temp;

    temp = currentDirectory->cd(2, args);

    while(temp != currentDirectory)
    {
      currentDirectory = temp;
      temp = currentDirectory->cd(2, args);
    } // while still moving up directory structure.

    ofstream outf("directories.txt");
    outf << *this;
    outf.close();
    return 0;
  }
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
  static const char *commands[] = {"cd", "chmod", "cp", "exit", "ls", "mkdir", "umask"};
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
      case 1 : chmod(argCount, arguments); break;
      case 2 : cp(argCount, arguments); break;
      case 3 : return eXit(argCount, arguments);
      case 4 : ls(argCount, arguments); break;
      case 5 : mkdir(argCount, arguments); break;
      case 6 : setUmask(argCount, arguments); break;
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
  short octal = 0;

  if(argCount != 2)
  {
    cout << "usage: umask octal\n";
    return;
  }

  for(int i = 0; arguments[1][i]; i++)
    if(!isdigit(arguments[1][i]) || arguments[1][i] == '9' || arguments[1][i] == '8')
    {
      cout << "usage: umask octal\n";
      return;
    }
    else
      octal = octal * 8 + arguments[1][i] - '0';


  if(octal < 0 || octal > 0777)
  {
    cout << "umask: octal must be between 0 and 777\n";
    return;
  } // if octal invalid

  umask = octal;
} // setUmask()


void Funix::writePrompt()
{
  currentDirectory->showPath();
  cout << " # ";
} // writePrompt()


istream& operator>> (istream &is, Funix &funix)
{
  is >> oct >> funix.umask;
  is.ignore();
  is >> *(funix.currentDirectory);
  return is;
} // operator>>


ostream& operator<< (ostream &os, Funix &funix)
{
  os << oct << funix.umask << endl;
  os << *(funix.currentDirectory);
  return os;
} // operator<<
