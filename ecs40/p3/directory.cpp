//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "directory.h"
using namespace std;


Directory* Directory::cd(int argCount, const char *arguments[])
{
  if(argCount != 2)
  {
    cout << "usage: cd directoryName\n";
    return this;
  } // if wrong number of arguments

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

  cout << arguments[1] << ": no such directory\n";
  return this;

} // cd()

void Directory::ls(int argCount, const char *arguments[]) const
{
  if(argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l")))
  {
    cout << "usage: ls [-l]\n";
    return;
  }  // if 

  if(subDirectoryCount == 0)
    return;
    
  if(argCount == 2) // must be ls -l
  {
   for(int i = 0; i < subDirectoryCount; i++)
   {
      subDirectories[i]->permissions.print();
      cout << " " << subDirectories[i]->time << " " << subDirectories[i]->name 
        << "\n";
    } // for each subdirectory
  } // if -l
  else // simple ls
  {
    for(int i = 0; i < subDirectoryCount; i++)
      cout << subDirectories[i]->name << " ";

    cout << "\n";
  } // else simple else
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
      << " already contains the maximum number of directories\n";
    return;
  } // if already at max subdirectories

  for(int i = 0; i < subDirectoryCount; i++)
    if(strcmp(arguments[1], subDirectories[i]->name) == 0)
    {
      cout << "mkdir: cannot create directory '" << arguments[1] 
        << "': File exists\n";
      return;
    } // for each sub directory

  subDirectories[subDirectoryCount]
    = new Directory(arguments[1], umask, time, this);
  
  subDirectoryCount++;

} // mkdir()


void Directory::showPath() const
{
  if(parent)
  {
    parent->showPath();
    cout << name << "/";
  } // if has a parent
  else // directory has no parent, i.e. the root
    cout << name;
} // showPath()

Directory::Directory(const char *dname, short umask, int time, Directory *parent)
  :time(time), subDirectoryCount(0), parent(parent)
  {
    name = new char[strlen(dname) + 1];
    strcpy(name, dname);
    permissions.set(7, umask);
  }//Directory Constructor

  Directory::~Directory()
  {
    delete[] name;
    for(int i = 0; i < subDirectoryCount; i++)
      delete subDirectories[i];
  }//Directory Destructor