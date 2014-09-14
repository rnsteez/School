//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
#include "funix.h"
#include "directory.h"
#include "permissions.h"

using namespace std;

char* Funix::user = new char[strlen("root" + 1)];

Funix::Funix()
{
  strcpy(user, "root");
  currentDirectory = new Directory("/", NULL);
  ifstream inf("directories.txt");

  if(inf)
  {
    inf >> *this; 
  }
  
} // Funix()


Funix::~Funix()
{
  const char *arguments[] = {"cd", ".."};
  Directory *temp;

  temp = currentDirectory->cd(2, arguments, user);

  while(temp != currentDirectory)
  {
    currentDirectory = temp;
    temp = currentDirectory->cd(2, arguments, user);
  } // while still moving up directory structure.

  delete currentDirectory;
} // ~Funix()


void Funix::cd( int argCount, const char *arguments[])
{
  currentDirectory = currentDirectory->cd(argCount, arguments, user);
} // cd()


void Funix::chmod( int argCount, const char *arguments[])
{
  currentDirectory->chmod(argCount, arguments, user);
} // chmod()


void Funix::cp( int argCount, const char *arguments[])
{
  currentDirectory->cp(argCount, arguments, user);
} // cp()


int Funix::eXit( int argCount, const char *arguments[])
{
  const char *args[] = {"cd", ".."};

  if(argCount == 1) // proper
  {
    Directory *temp;

    temp = currentDirectory->cd(2, args, user);

    while(temp != currentDirectory)
    {
      currentDirectory = temp;
      temp = currentDirectory->cd(2, args, user);
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
  currentDirectory->ls(argCount, arguments, user);
} // ls()


void Funix::mkdir( int argCount, const char *arguments[])
{
  currentDirectory->mkdir( argCount, arguments, user);
} // mkdir()


int Funix::processCommand( char *command)
{
  static const char *commands[] = {"cd", "chmod", "cp", "exit", "ls", "mkdir", "umask", "su", "chown"};
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
    for(commandNum = 0; commandNum < 9; commandNum++)
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
      case 7 : su(argCount, arguments); break;
      case 8 : chown(argCount, arguments); break;
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

  Permissions::setUmask(octal);
} // setUmask()


void Funix::writePrompt()
{
  currentDirectory->showPath();
  cout << " # ";
} // writePrompt()


void Funix::su(int argCount, const char *arguments[])
{
  if (argCount != 2)
    cout << "usage: su user_name\n";
  else // valid su
  {
    delete [] user;
    user = new char[strlen(arguments[1] + 1)];
    strcpy(user, arguments[1]);
  }
}


void Funix::chown(int argCount, const char *arguments[])
{
  currentDirectory->chown(argCount, arguments);
}//change owner


istream& operator>> (istream &is, Funix &funix)
{
  char user[80];
  is >> user;
  delete [] funix.user;
  funix.user = new char[strlen(user) + 1];
  strcpy(funix.user, user);
  
  short umask;
  is >> oct >> umask >> dec;
  Permissions::setUmask(umask);
  
  is >> *(funix.currentDirectory);
  return is;
} // operator>>


ostream& operator<< (ostream &os, Funix &funix)
{
  short umask = Permissions::getUmask();
  os << funix.user << ' ' << oct << umask << dec << endl;
  os << *(funix.currentDirectory);
  return os;
} // operator<<
