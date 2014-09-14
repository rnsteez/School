// Author: Sean Davis
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "directory.h"
#include "Time.h"
#include "permissions.h"
#include "linkedlist.h"
#include "file.h"

using namespace std;

Directory::Directory(const char *nam, Directory *paren, const char* owner)
  : File(nam, Permissions(01777, owner)),  subDirectoryCount(0), parent(paren)
{
} // Directory()


Directory::Directory(const Directory &rhs) : File(rhs),
  subDirectoryCount(rhs.subDirectoryCount), parent(rhs.parent)
{
  for(int i = 0; i < subDirectoryCount; i++)
  {
    if(rhs.subDirectories[i]->isFile())
      subDirectories += new File(*(rhs.subDirectories[i]));
    else
    {
      Directory *temp = new Directory(*((Directory*) rhs.subDirectories[i]));
      temp->parent = this;
      subDirectories += temp;
    }
  }
} // Directory copy constructor


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
      if(! parent->checkPermissions(1, user))
      {
        cout << "cd: Permission denied.\n";
        return this;
      } // if incorrect permissions
      return parent;
    } // if not root
    else
      return this;
  } // if cd ..

  for(int i = 0; i < subDirectoryCount; i++)
    if(Directory(arguments[1]) == *subDirectories[i])
    {
      if(! subDirectories[i]->checkPermissions(1, user) || subDirectories[i]->isFile())
      {
        cout << "cd: Permission denied.\n";
        return this;
      } // if incorrect permissions for this subdirectory
      return (Directory*) subDirectories[i];
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
      if(*subDirectories[j] == File(arguments[i]))
      {
        subDirectories[j]->changePermissions(value);
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
        subDirectories[j]->chown(arguments[1]);
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
  } // if didn't find file

  if(!strcmp(arguments[1], arguments[2]))
  {
    cout << "cp: '" << arguments[1] << "' and '" << arguments[2]
      << "' are the same file\n";
    return;
  } // if same names


  for(int j = 0; j < subDirectoryCount; j++)
    if(*subDirectories[j] == File(arguments[2]))
    {
      cout << "cp: omitting '" << arguments[2] << "'\n";
      return;
     }  // if duplicate names


  if(! subDirectories[i]->checkPermissions(4, user))
  {
    cout << "cp : Permission denied.\n";
    return;
  } // if permissions not OK

  if(subDirectories[i]->isFile())
  {
    File *temp = new File(*subDirectories[i]);
    temp->rename(arguments[2]);
    temp->chown(user);
    subDirectories += temp;
  }
  else
  {
    Directory *temp = new Directory(*((Directory*) subDirectories[i]));
    temp->parent = this;
    temp->rename(arguments[2]);
    ((File*)temp)->chown(user);
    subDirectories += temp;
  } // else subdirectory is a Directory

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

  if(!checkPermissions(4, user))
  {
    cout << "ls: Permission denied.\n";
    return;
  } // if invalid permissions

  for(int i = 0; i < subDirectoryCount; i++)
      subDirectories[i]->print(argCount == 2);
  if(argCount != 2)
    cout << endl;
} // ls()

void Directory::mkdir(int argCount, const char *arguments[], const char *user)
{
  if(argCount != 2)
  {
    cout << "usage: mkdir directory_name\n";
    return;
  } // if wrong number of arguments

  for(int i = 0; i < subDirectoryCount; i++)
    if(File(arguments[1]) == *subDirectories[i])
    {
      cout << "mkdir: cannot create directory '" << arguments[1]
        << "': File exists\n";
      return;
    } // if found file with same name

  if(! checkPermissions(6, user))
  {
    cout << "mkdir: Permission denied.\n";
    return;
  } // if don't have permissions

  subDirectories += new Directory(arguments[1], this, user);
  subDirectoryCount++;
  File::touch();

} // mkdir()

ostream& Directory::write(ostream &os)  const
{
  os << 'D';
  File::write(os);
  os << subDirectoryCount << endl;

  for(int i = 0; i < subDirectoryCount; i++)
    os << *(subDirectories[i]);

  return os;
} // print()

void Directory::showPath() const
{
  if(parent)
  {
    parent->showPath();
    showName();
    cout << "/";
  } // if not root
  else
    showName();
} // showPath()

void Directory::touch(int argCount, const char *arguments[], const char *user)
{
  int i, j;

  if(argCount < 2)
  {
    cout << "touch: too few arguments\n";
    return;
  } // if incorrect argument count.


  for(i = 1; i < argCount; i++)
  {
    for(j = 0; j < subDirectoryCount; j++)
      if(*subDirectories[j] == File(arguments[i]))
      {
        if(! subDirectories[j]->checkPermissions(2, user))
          cout << "touch: Permission denied.\n";
        else
          subDirectories[j]->touch();

        break;
      } // if found subdirectory match

    if(j == subDirectoryCount)
    {
      if(! checkPermissions(2, user))
        cout << "touch: Permission denied.\n";
      else
      {
        subDirectories += new File(arguments[i], Permissions(0666, user));
        subDirectoryCount++;
      }
    }
  } // for each file
} // touch()


istream& operator>> (istream &is, Directory &directory)
{
  char type;

  is >> (File&) directory;
  is >> directory.subDirectoryCount;


  for(int i = 0; i < directory.subDirectoryCount; i++)
  {
    is >> type;
    if(type == 'D')
    {
      Directory *subDirectory = new Directory("Dummy");
      is >> type;
      is >> *subDirectory;
      subDirectory->parent = &directory;
      directory.subDirectories += subDirectory;
    }
    else
    {
      File *file = new File("Dummy");
      is >> *file;
      directory.subDirectories += file;
    }
  } // for each subdirectory

  return is;
}  // operator>>


