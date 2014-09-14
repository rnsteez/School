// Author: Sean Davis
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "directory.h"
#include "Time.h"
#include "permissions.h"

using namespace std;

Directory::Directory(const char *nam, short umask,
  Directory *paren): subDirectoryCount(0), parent(paren)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(0777, umask);
} // Directory()


Directory::Directory(const Directory &rhs) : subDirectoryCount(rhs.subDirectoryCount), 
  permissions(rhs.permissions),  parent(rhs.parent)
{
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
  for(int i = 0; i < rhs.subDirectoryCount; i++)
  {
    subDirectories[i] = new Directory(*(rhs.subDirectories[i]));
    subDirectories[i]->parent = this;
  }
} // Directory copy constructor


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
  } // if not two arguments

  if(strcmp(arguments[1], "..") == 0)
  {
    if(parent)
      return parent;
    else
      return this;
  }  //  if moving up to parent.

  for(int i = 0; i < subDirectoryCount; i++)
    if(Directory(arguments[1]) == *subDirectories[i])
      return subDirectories[i];

  cout << arguments[1] << ": no such file or directory.\n";
  return this;
} // cd()



void Directory::chmod(int argCount, const char *arguments[])
{
  int i, j, value = 0;

  if(argCount < 3)
  {
    cout << "chmod: too few arguments\n";
    return;
  } // if incorrect argument count.

  for(i = 0; arguments[1][i]; i++)
    if(! isdigit(arguments[1][i]) || arguments[1][i] == '9'
      || arguments[1][i] == '8')
    {
      cout << "chmod: invalid mode string: '" << arguments[1] << "'\n";
      return;
    }
    else
      value = 8 * value + arguments[1][i] - '0';

  if(value < 0 || value > 0777)
  {
    cout << "chmod: invalid mode string: '" << arguments[1] << "'\n";
    return;
  } // if invalid value

  for(i = 2; i < argCount; i++)
  {
    for(j = 0; j < subDirectoryCount; j++)
      if(*subDirectories[j] == Directory(arguments[i]))
      {
        subDirectories[j]->permissions.set(value, 0);
        break;
      } // if found matching directory name

    if(j == subDirectoryCount)
      cout << "chmod: failed to get attributes of '" << arguments[i]
        << "': No such file or directory\n";
  }
} // chmod()


void Directory::cp( int argCount, const char *arguments[])
{
  int i, j;
  
  if(subDirectoryCount == MAX_DIRECTORIES)
  {
    cout << "cp: " << name
      <<  " already contains the maximum number of directories\n";
    return;
  } // if already at maximum

  if(argCount == 1)
  {
    cout << "cp: missing file arguments\n";
    return;
  } // if incorrect argument count.

  if(argCount == 2)
  {
    cout << "cp: missing destination file\n";
    return;
  } // if incorrect argument count.

  if(argCount > 3)
  {
    cout << "cp: too many arguments\n";
    return;
  } // if incorrect argument count.


  for(i = 0; i < subDirectoryCount; i++)
    if(*subDirectories[i] == Directory(arguments[1]))
      break;

  if(i == subDirectoryCount)
  {
    cout << "cp: cannot stat '" << arguments[1]
      << "': No such file or directory\n";
    return;
  } // if didn't find the directory

  if(!strcmp(arguments[1], arguments[2]))
  {
    cout << "cp: '" << arguments[1] << "' and '" << arguments[2]
      << "' are the same file\n";
    return;
  } // if argumuents are the same

  for(j = 0; j < subDirectoryCount; j++)
    if(*subDirectories[j] == Directory(arguments[2]))
    {
      cout << "cp: omitting directory '" << arguments[2] << "'\n";
      return;
     }  // if duplicate names


  subDirectories[subDirectoryCount]
    = new Directory(*subDirectories[i]);
  delete subDirectories[subDirectoryCount]->name;
  subDirectories[subDirectoryCount]->name = new char[strlen(arguments[2]) + 1];
  strcpy(subDirectories[subDirectoryCount++]->name, arguments[2]);
  modificationTime.update();
} // cp()



void Directory::ls(int argCount, const char *arguments[])const
{
  if(argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l")))
  {
    cout << "usage: ls [-l]\n";
    return;
  } // if incorrect number of arguments

  if(subDirectoryCount == 0)
    return;

  if(argCount == 2) // must be ls -l
  {
    for(int i = 0; i < subDirectoryCount; i++)
    {
      subDirectories[i]->permissions.print();
      cout << " ";
      subDirectories[i]->modificationTime.print();
      cout << ' ' << subDirectories[i]->name << endl;
    } // for each subdirectory
  } // if ls -l
  else // simple ls
  {
    for(int i = 0; i < subDirectoryCount; i++)
      cout << subDirectories[i]->name << " ";

    cout << endl;
  } // else simple ls
} // ls()


void Directory::mkdir(int argCount, const char *arguments[],
  short umask)
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
  } // if already at MAX DIRECTORIES

  for(int i = 0; i < subDirectoryCount; i++)
    if(strcmp(arguments[1], subDirectories[i]->name) == 0)
    {
      cout << "mkdir: cannot create directory '" << arguments[1]
        << "': File exists\n";
      return;
    } // if directory already contains same name

  subDirectories[subDirectoryCount++]
    = new Directory(arguments[1], umask, this);

  modificationTime.update();

} // mkdir()


void Directory::showPath() const
{
  if(parent)
  {
    parent->showPath();
    cout << name << "/";
  } // if directory is not root
  else
    cout << name;
} // showPath()


bool Directory::operator== (const Directory &rhs) const
{
  return !strcmp(name, rhs.name);
} // operator==



ostream& operator<< (ostream &os, const Directory &directory)
{
  os << directory.name << ' ' <<  directory.modificationTime << directory.permissions
    << directory.subDirectoryCount << endl;

  for(int i = 0; i < directory.subDirectoryCount; i++)
    os << *(directory.subDirectories[i]);

  return os;
}  // operator<<


istream& operator>> (istream &is, Directory &directory)
{
  char name[80];
  is >> name;
  delete [] directory.name;
  directory.name = new char[strlen(name) + 1];
  strcpy(directory.name, name);
  is.ignore();  // eat space char
  is >> directory.modificationTime >> directory.permissions
    >> directory.subDirectoryCount;

  for(int i = 0; i < directory.subDirectoryCount; i++)
  {
    directory.subDirectories[i] = new Directory("Dummy", 0, &directory);
    is >> *directory.subDirectories[i];
  } // for each subdirectory

  return is;
}  // operator<<
