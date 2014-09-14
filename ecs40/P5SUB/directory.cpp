//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "directory.h"
#include "Time.h"
#include "permissions.h"
#include "linkedlist.h"
#include "funix.h"

using namespace std;

Directory::Directory(const char *nam,
  Directory *paren): subDirectoryCount(0), parent(paren)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(0777);
} // Directory()


Directory::Directory(const Directory &rhs) : subDirectoryCount(rhs.subDirectoryCount), 
  permissions(rhs.permissions),  parent(rhs.parent)
{
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
} // Directory copy constructor


Directory::~Directory()
{
  delete [] name;
} // ~Directory()


Directory* Directory::cd(int argCount, const char *arguments[], 
  const char* user)
{
  if(argCount != 2)
  {
    cout << "usage: cd directoryName\n";
    return this;
  } // if not two arguments

  if(strcmp(arguments[1], "..") == 0)
  {
    if(parent)
    {
      if(parent->permissions.check(user) & 5)
        return parent;
      else // You require additional permissions
      {
        cout << "cd: Permission denied.\n";
        return this;
      }
    }
    else // at root
      return this;
  }  //  if moving up to parent.

  for(int i = 0; i < subDirectoryCount; i++)
    if(Directory(arguments[1]) == *subDirectories[i])
    {
      if(subDirectories[i]->permissions.check(user) & 5)
        return subDirectories[i];
      else // You require additional permissions
      {
        cout << "cd: Permission denied.\n";
        return this;
      }
    }
  
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
        if((subDirectories[j]->permissions.check(user) & 2) 
          || subDirectories[j]->permissions.checkOwn(user))
        {
          subDirectories[j]->permissions.chmod(value);
          break;
        }
        else // You require additional permissions
        {
          cout << "chmod: Permission denied.\n";
          break;
        }
      } // if found matching directory name

    if(j == subDirectoryCount)
      cout << "chmod: failed to get attributes of '" << arguments[i]
        << "': No such file or directory\n";
  }
} // chmod()


void Directory::cp( int argCount, const char *arguments[], const char *user)
{
  int i, j;

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

    if((permissions.check(user) & 2) 
      && (subDirectories[i]->permissions.check(user) & 4))
    {
      subDirectories += new Directory(arguments[2], this);
      subDirectoryCount++;
      for(int k = 0; k < subDirectoryCount; k++)
        if(*subDirectories[k] == Directory(arguments[2]))
        {
          subDirectories[k]->subDirectories = subDirectories[i]->subDirectories;
          subDirectories[k]->subDirectoryCount = subDirectories[i]->subDirectoryCount;
          for (int l = 0; l < subDirectories[k]->subDirectoryCount; l++)
            subDirectories[k]->subDirectories[l]->parent = subDirectories[k];
        }

      modificationTime.update();
    }
    else
      cout << "cp : Permission denied.\n"; 
      
} // cp()



void Directory::ls(int argCount, const char *arguments[], const char *user) const
{
  if(argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l")))
  {
    cout << "usage: ls [-l]\n";
    return;
  } // if incorrect number of arguments

  if(permissions.check(user) & 4)
  {
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
  }// test perm
  else // You require additional permissions
  {
    cout << "ls: Permission denied.\n";
  }// no perm   
} // ls()

void Directory::mkdir(int argCount, const char *arguments[], const char *user)
{
  if(argCount != 2)
  {
    cout << "usage: mkdir directory_name\n";
    return;
  } // if wrong number of arguments

  if(permissions.check(user) & 2)   
  {   
  for(int i = 0; i < subDirectoryCount; i++)     
    if(strcmp(arguments[1], subDirectories[i]->name) == 0)
    {
      cout << "mkdir: cannot create directory '" << arguments[1]
        << "': File exists\n";
      return;
    } // if directory already contains same name 
  
    subDirectories += new Directory(arguments[1], this);
    subDirectoryCount++;
    modificationTime.update();
  }
  else // You require additional permission
  {
    cout << "mkdir: Permission denied.\n";
  }

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


void Directory::chown( int argCount, const char *arguments[])
{
  if (argCount < 3)
  {
    cout << "chown: too few arguments\n";
    return;
  }
  if (!strcmp(Funix::user, "root"))
  {
    for (int j = 2; j < argCount; j++)
    {
      for (int i = 0; i < subDirectoryCount; i++)
      {
        if (*subDirectories[i] == Directory(arguments[j]))
          subDirectories[i]->permissions.setOwner(arguments[1]);
      }
    }
  }
  else // You require additional permissions
    cout << "chown: Permission denied\n";

}//chown


bool Directory::operator== (const Directory &rhs) const
{
  return !strcmp(name, rhs.name);
} // operator==


bool Directory::operator< (const Directory &rhs) const
{
  if (strcmp(name, rhs.name) < 0)
    return 1;
  else // rhs < lhs or rhs == lhs
    return 0;
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
  char name[80];
  if (!strcmp(directory.name, "/"))
  {
    is >> name;
    delete [] directory.name;
    directory.name = new char[strlen(name) + 1];
    strcpy(directory.name, name);
    is.ignore();  // eat space char
    is >> directory.modificationTime >> directory.permissions
      >> directory.subDirectoryCount;
    is.ignore();
  }

  for(int i = 0; i < directory.subDirectoryCount; i++)
  {
    is >> name;
    directory.subDirectories += new Directory(name, &directory);
    is >> directory.subDirectories[i]->modificationTime >> directory.subDirectories[i]->permissions
      >> directory.subDirectories[i]->subDirectoryCount;
    is >> *directory.subDirectories[i];
  } // for each subdirectory

  return is;
}  // operator<<
