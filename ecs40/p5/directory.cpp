// Author: Sean Davis
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "directory.h"
#include "Time.h"
#include "permissions.h"

using namespace std;

Directory::Directory(const char *nam, Directory *paren, const char* owner)
  : subDirectoryCount(0), permissions(0777, owner), parent(paren)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
} // Directory()


Directory::Directory(const Directory &rhs) : subDirectoryCount(rhs.subDirectoryCount), 
  permissions(rhs.permissions),  parent(rhs.parent)
{
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);

  for(int i = 0; i < subDirectoryCount; i++)
  {
    Directory *temp = new Directory(*((Directory*) rhs.subDirectories[i]));
    temp->parent = this;
    subDirectories += temp;
  }  // for each subdirectory
} // Directory copy constructor


Directory::~Directory()
{
  delete [] name;
} // ~Directory()


Directory* Directory::cd(int argCount, const char *arguments[], const char *user)
{
  if(argCount != 2)
  {
    cout << "usage: cd directoryName\n";
    return this;
  } // if incorrect number of arguments

  if(strcmp(arguments[1], "..") == 0)
  {
    if(parent)
    {
      if(! parent->permissions.check(5, user))
      {
        cout << "cd: Permission denied.\n";
        return this;
      } // if incorrect permissions
      return parent;
    }
    else // root directory
      return this;
  } // if cd ..

  for(int i = 0; i < subDirectoryCount; i++)
    if(Directory(arguments[1]) == *subDirectories[i])
    {
      if(! subDirectories[i]->permissions.check(5, user))
      {
        cout << "cd: Permission denied.\n";
        return this;
      } // if incorrect permissions for this subdirectory

      return subDirectories[i];
    } // if found subdirectory match

  cout << arguments[1] << ": no such file or directory.\n";
  return this;
} // cd()



void Directory::chmod(int argCount, const char *arguments[], const char *user)
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
    } // if invalid mode
    else // valid digit
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
        if(strcmp(user, "root") && strcmp(user, subDirectories[j]->permissions.getOwner()) != 0 
          && ! subDirectories[j]->permissions.check(2, user))
        {
          cout << "chmod: Permission denied.\n";
          return;
        } // if invalid permissions for subdirectory

        subDirectories[j]->permissions.chmod(value);
        break;
      } // if found subdirectory match

    if(j == subDirectoryCount)
      cout << "chmod: failed to get attributes of '" << arguments[i]
        << "': No such file or directory\n";
  } // for each file
} // chmod()


void Directory::chown( int argCount, const char *arguments[], const char *user)
{
  int i, j;

  if(argCount < 3)
  {
    cout << "chown: too few arguments\n";
    return;
  } // if incorrect argument count.


  for(i = 2; i < argCount; i++)
  {
    for(j = 0; j < subDirectoryCount; j++)
      if(*subDirectories[j] == Directory(arguments[i]))
      {
        if(strcmp("root", user))
        {
          cout << "chown: Permission denied.\n";
          return;
        } // if invalid permissions for subdirectory

        subDirectories[j]->permissions.setOwner(arguments[1]);
        break;
      } // if found subdirectory match

    if(j == subDirectoryCount)
      cout << "chown: failed to get attributes of '" << arguments[i]
        << "': No such file or directory\n";
  } // for each file in arguments

} // chown()


void Directory::cp( int argCount, const char *arguments[], const char *user)
{
  int i;


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
    cout << "cp: too many arguments";
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
  } // if didn't find file

  if(!strcmp(arguments[1], arguments[2]))
  {
    cout << "cp: '" << arguments[1] << "' and '" << arguments[2]
      << "' are the same file\n";
    return;
  } // if same names


  if(! subDirectories[i]->permissions.check(4, user))
  {
    cout << "cp : Permission denied.\n";
    return;
  } // if permissions not OK

  Directory *temp = new Directory(*subDirectories[i]);
  delete temp->name;
  temp->name = new char[strlen(arguments[2]) + 1];
  strcpy(temp->name, arguments[2]);
  temp->permissions.setOwner(user);
  subDirectories += temp;
  subDirectoryCount++;
} // cp()



void Directory::ls(int argCount, const char *arguments[], const char *user)const
{
  if(argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l")))
  {
    cout << "usage: ls [-l]\n";
    return;
  } // if incorrect number of arguments

  if(subDirectoryCount == 0)
    return;

  if(!permissions.check(4, user))
  {
    cout << "ls: Permission denied.\n";
    return;
  } // if invalid permissions
  
  if(argCount == 2) // must be ls -l
  {
    for(int i = 0; i < subDirectoryCount; i++)
    {
      subDirectories[i]->permissions.print();
      cout << " ";
      subDirectories[i]->modificationTime.print();
      cout << ' ' << subDirectories[i]->name << endl;
    }  // for each subdirectory
  } // if ls -l
  else // simple ls
  {
    for(int i = 0; i < subDirectoryCount; i++)
      cout << subDirectories[i]->name << " ";

    cout << endl;
  } // else simple ls
} // ls()

void Directory::mkdir(int argCount, const char *arguments[], const char *user)
{
  if(argCount != 2)
  {
    cout << "usage: mkdir directory_name\n";
    return;
  } // if wrong number of arguments

  for(int i = 0; i < subDirectoryCount; i++)
    if(strcmp(arguments[1], subDirectories[i]->name) == 0)
    {
      cout << "mkdir: cannot create directory '" << arguments[1]
        << "': File exists\n";
      return;
    } // if found file with same name

  if(! permissions.check(6, user))
  {
    cout << "mkdir: Permission denied.\n";
    return;
  } // if don't have permissions 

  subDirectories += new Directory(arguments[1], this, user);
  subDirectoryCount++;
  modificationTime.update();

} // mkdir()


void Directory::showPath() const
{
  if(parent)
  {
    parent->showPath();
    cout << name << "/";
  } // if not root
  else
    cout << name;
} // showPath()


bool Directory::operator== (const Directory &rhs) const
{
  return !strcmp(name, rhs.name);
} // operator==


bool Directory::operator< (const Directory &rhs) const
{
  return strcmp(name, rhs.name) < 0;
} // operator<


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
  char temp[80];
  is >> temp;
 
  if(directory.name)
    delete [] directory.name;

  directory.name = new char[strlen(temp) + 1];
  strcpy(directory.name, temp);
  
  is.ignore();  // eat space char
  is >> directory.modificationTime >> directory.permissions
    >> directory.subDirectoryCount;


  for(int i = 0; i < directory.subDirectoryCount; i++)
  {
    Directory *subDirectory = new Directory("Dummy");
    is >> *subDirectory;
    subDirectory->parent = &directory;
    directory.subDirectories += subDirectory;
  } // for each subdirectory

  return is;
}  // operator<<
