// Author: Sean Davis
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "directory.h"

using namespace std;

Directory::Directory(const char *nam, short umask,
  int tim, Directory *paren): time(tim), subDirectoryCount(0), parent(paren)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(7, umask);
} // createDirectory()


Directory::~Directory()
{
  delete [] name;

  for(int i = 0; i < subDirectoryCount; i++)
    delete subDirectories[i];
} // ~Directory()


Directory* Directory::cd(int argCount, const char *arguments[])
{
  if(argCount != 2)
  {
    cout << "usage: cd directoryName\n";
    return this;
  } // if incorrect number of arguments

  if(strcmp(arguments[1], "..") == 0)
  {
    if(parent)
      return parent;
    else
      return this;
  } // if cd ..

  for(int i = 0; i < subDirectoryCount; i++)
    if(strcmp(arguments[1], subDirectories[i]->name) == 0)
      return subDirectories[i];

  cout << arguments[1] << ": no such file or directory.\n";
  return this;
} // cd()



void Directory::ls(int argCount, const char *arguments[])const
{
  if(argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l")))
  {
    cout << "usage: ls [-l]\n";
    return;
  } // if incorrect number of arguments or second argument is not -l

  if(subDirectoryCount == 0)
    return;

  if(argCount == 2) // must be ls -l
  {
    for(int i = 0; i < subDirectoryCount; i++)
    {
      subDirectories[i]->permissions.print();
      cout << " " << subDirectories[i]->time <<  ' ' << subDirectories[i]->name << endl;
    }  // for each subdirectory
  } // if ls -l
  else // simple ls
  {
    for(int i = 0; i < subDirectoryCount; i++)
      cout << subDirectories[i]->name << " ";

    cout << endl;
  } // else simple ls
} // ls()


void Directory::mkdir(int argCount, const char *arguments[],
  short umask, int time)
{
  if(argCount != 2)
  {
    cout << "usage: mkdir directory_name\n";
    return;
  } // if wrong number of arguments

  if(subDirectoryCount == MAX_DIRECTORIES)
  {
    cout << "mkdir: " << name
      <<  " already contains the maximum number of directories\n";
    return;
  } // if already have maximum number of directories

  for(int i = 0; i < subDirectoryCount; i++)
    if(strcmp(arguments[1], subDirectories[i]->name) == 0)
    {
      cout << "mkdir: cannot create directory '" << arguments[1]
        << "': File exists\n";
      return;
    } // if found subdirectory with name already exists.

  subDirectories[subDirectoryCount++]
    = new Directory(arguments[1], umask, time, this);

} // mkdir()


void Directory::showPath() const
{
  if(parent)
  {
    parent->showPath();
    cout << name << "/";
  } // if parent then call it
  else
    cout << name;
} // showPath()


