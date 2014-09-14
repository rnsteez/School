//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "directory.h"
#include "Time.h"
#include "permissions.h"

using namespace std;

Directory::Directory(const char *nam, Directory *paren, const char* owner)
  : File(nam, Permissions(01777, owner)), subDirectoryCount(0), parent(paren)
{
  
} // Directory()


Directory::Directory(const Directory &rhs) : File(rhs),
  subDirectoryCount(rhs.subDirectoryCount), parent(rhs.parent)
{

  for(int i = 0; i < subDirectoryCount; i++)
  {
    if (!rhs.subDirectories[i]->isFile())
    {
      Directory *temp = new Directory(*((Directory*) rhs.subDirectories[i]));
      temp->parent = this;
      subDirectories += temp;
    }
    else // is a file
    {
      File *temp = new File(*((File*) rhs.subDirectories[i]));
      subDirectories += temp;
    }
  }  // for each subdirectory or subfile
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
      if(! parent->checkPermissions(5, user))
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
      if((! subDirectories[i]->checkPermissions(5, user)) || subDirectories[i]->isFile())
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
        if(strcmp(user, "root") && strcmp(user, subDirectories[j]->getOwner()) != 0 
          && ! subDirectories[j]->checkPermissions(2, user))
        {
          cout << "chmod: Permission denied.\n";
          return;
        } // if invalid permissions for subdirectory

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
  
  for(int j = 0; j < subDirectoryCount; j++)
  {
    if(*subDirectories[j] == Directory(arguments[2]))
    {
      cout << "cp: omitting directory '" << arguments[2] << "'\n";
      return;
    }  // if duplicate names
  }

  if(! subDirectories[i]->checkPermissions(4, user))
  {
    cout << "cp : Permission denied.\n";
    return;
  } // if permissions not OK

  if (!subDirectories[i]->isFile())
  {
    Directory *temp = new Directory(*((Directory*) subDirectories[i]));
    temp->rename(arguments[2]);
    temp->File::chown(user);
    subDirectories += temp;
  }
  else // is a file
  {
    File *temp = new File(*((File*) subDirectories[i]));
    temp->rename(arguments[2]);
    temp->chown(user);
    subDirectories += temp;
  }
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
  
  if(argCount == 2) // must be ls -l
  {
    for(int i = 0; i < subDirectoryCount; i++)
    {
      subDirectories[i]->print();
      cout << ' ' << subDirectories[i]->showName() << endl;
    }  // for each subdirectory
  } // if ls -l
  else // simple ls
  {
    for(int i = 0; i < subDirectoryCount; i++)
      cout << subDirectories[i]->showName() << " ";

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
    if(strcmp(arguments[1], subDirectories[i]->showName()) == 0)
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
  timeUpdate();

} // mkdir()


void Directory::touch(int argCount, const char *arguments[], const char *user)
{
  if(argCount < 2)
  {
    cout << "touch: too few arguments\n";
    return;
  } // if wrong number of arguments

  if(! checkPermissions(6, user))
  {
    cout << "touch: Permission denied.\n";
    return;
  } // if don't have permissions 
  
  for(int i = 1; i < argCount; i++)
  {
    int test = 1;
    for(int j = 0; j < subDirectoryCount; j++)
    {
      if(strcmp(arguments[i], subDirectories[j]->showName()) == 0)
      {
        if(subDirectories[j]->checkPermissions(2, user))
        {
          subDirectories[j]->timeUpdate();
          test = 0;
        }
        else // user does not have write permissions in subDirectories[j]
        {
          cout << "touch: Permission denied.\n";
          test = 0;
        }
      } // if found file with same name
    }
    if (test)
    {
      subDirectories += File::touch(arguments[i], user);
      subDirectoryCount++;
    }
  }

} // touch()


void Directory::showPath() const
{
  if(parent)
  {
    parent->showPath();
    cout << showName() << "/";
  } // if not root
  else
    cout << showName();
} // showPath()


ostream& Directory::write(ostream &os, const Directory &directory) const
{
  os << 'D';
  directory.File::write(os, directory);
  
  os << directory.subDirectoryCount << endl;
  
  for(int i = 0; i < directory.subDirectoryCount; i++)
  {
    if (directory.subDirectories[i]->isFile())
      os << *((File*)directory.subDirectories[i]);
    else // is a directory
      os << *((Directory*)directory.subDirectories[i]);
  }

  return os;
}//write()


ostream& operator<< (ostream &os, const Directory &directory)
{
  directory.write(os, directory);
  return os;
}  // operator<<


istream& operator>> (istream &is, Directory &directory)
{
  is >> (File&) directory;

  char test = is.get();
  is >> directory.subDirectoryCount;
  test = is.get();

  for(int i = 0; i < directory.subDirectoryCount; i++)
  {
    test = is.get();
    if (test == 'D')
    {
      is.ignore(1);
      Directory *subDirectory = new Directory("Dummy");
      is >> *subDirectory;
      subDirectory->parent = &directory;
      directory.subDirectories += subDirectory;
    }
    else // is a file
    {
      File *subFile = new File("Dummy");
      is >> *subFile;
      directory.subDirectories += subFile;
      is.ignore();
    }
  } // for each subdirectory

  return is;
}  // operator<<
