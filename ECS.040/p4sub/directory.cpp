//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "directory.h"

using namespace std;

Directory::Directory(const char *nam, Permissions umask,
  Directory *paren): subDirectoryCount(0), parent(paren)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(umask);
} // createDirectory()


Directory::Directory(const char *nam)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  parent = NULL;
}


Directory::~Directory()
{
  delete [] name;

  for(int i = 0; i < subDirectoryCount; i++)
    delete subDirectories[i];
} // ~Directory()

Directory::Directory(const Directory& ori) :subDirectoryCount(ori.subDirectoryCount), 
permissions(ori.permissions), parent(ori.parent)
{
  name = new char[strlen(ori.name) + 1];
  strcpy(name, ori.name);
  for (int i = 0; i < ori.subDirectoryCount; i++)
    subDirectories[i] = new Directory(*(ori.subDirectories[i]));
}//copy constructor

bool Directory::operator==(const Directory &rhs) const
{
  if(!strcmp(name, rhs.name))
    return 1;
  else
    return 0;
}


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
  
  Directory test(arguments[1]);
  for(int i = 0; i < subDirectoryCount; i++)
    if(test == *subDirectories[i])
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
      cout << *subDirectories[i];
    }  // for each subdirectory
  } // if ls -l
  else // simple ls
  {
    for(int i = 0; i < subDirectoryCount; i++)
      cout << subDirectories[i]->name << " ";

    cout << endl;
  } // else simple ls
} // ls()


void Directory::mkdir(int argCount, const char *arguments[], Permissions umask)
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
    = new Directory(arguments[1], umask, this);

} // mkdir()


void Directory::chmod( int argCount, const char *arguments[])
{
  short octal;
  short test[3];

  if(argCount < 3)
  {
    cout << "chmod: too few arguments\n";
    return;
  } // if incorrect number of arguments

  for(int i = 0; arguments[1][i]; i++)
    if(!isdigit(arguments[1][i]))
    {
      cout << "chmod: invalid mode string: '" << arguments[1] << "'\n";
      return;
    } // if argument contains non-digit

  if (strlen(arguments[1]) > 3)
  {
    for(int i = 0; arguments[1][i] < (int) strlen(arguments[1]) - 3; i++)
    if(arguments[1][i] != 0)
    {
      cout << "chmod: invalid mode string: '" << arguments[1] << "'\n";
      return;
    }
  } // if there is any number except 0 before last 3 digits
  
  for(int i = 0; arguments[1][i]; i++)
      test[i] = arguments[1][i] - '0';
  
  for(int i = 0; arguments[1][i]; i++)
  {
  if(test[i] < 0 || test[i] > 7)
    {
      cout << "chmod: invalid mode string: '" << arguments[1] << "'\n";
      return;
    } // if octal invalid
  }
  
  octal = atoi(arguments[1]);
  
  int test2;
  for(int i = 2; i < argCount; i++)
  {
    test2 = 1;
    Directory testDirectory(arguments[i]);
    for(int j = 0; j < subDirectoryCount; j++)
    {
      if(*subDirectories[j] == testDirectory)
      {
        test2 = 0;
        subDirectories[j]->permissions.chmod(octal);
        break;
      }
    }
    if(test2)
    {
      cout << "chmod: failed to get attributes of '" << arguments[i] 
        << "': No such file or directory\n";
    }
  }   
} // chmod()


void Directory::cp(int argCount, const char *arguments[])
{
  switch(argCount)
  {
    case 1:
      cout << "cp: missing file arguments\n";
      break;
    case 2:
      cout << "cp: missing destination file\n";
      break;
    case 3:
    {
      if (subDirectoryCount == MAX_DIRECTORIES)
      {
        cout << "cp: ";
        showPath();
        cout << " already contains the maximum number of directories\n";
        return;
      }
      
      Directory test1(arguments[1]);
      Directory test2(arguments[2]);
      for (int i = 0; i < subDirectoryCount; i++)
      {
        if (test1 == *subDirectories[i])
        {
          if (test1 == test2)
          {
            cout<<"cp: '" << test1.name << "' and '" << test1.name 
              << "' are the same file\n";
            return;
          }
          for (int j = 0; j < subDirectoryCount; j++)
          {
            if (test2 == *subDirectories[j])
            {
              cout << "cp: omitting directory '" << arguments[2] << "'\n";
              return;
            }
          }
          
          //Valid cp  
          subDirectories[subDirectoryCount] = new Directory(*(subDirectories[i]));
          delete subDirectories[subDirectoryCount]->name; 
          subDirectories[subDirectoryCount]->name = new char[strlen(arguments[2]) + 1];
          strcpy(subDirectories[subDirectoryCount++]->name, arguments[2]);
          return;
        }
        
      } 
      cout << "cp: cannot stat '" << test1.name << "': No such file or directory\n";
    }
      break;
    default:
      cout << "cp: too many arguments\n";
  }
 
} //cp()


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


ofstream& operator<<(ofstream &os, const Directory &currentDirectory)
{
  os << (string) currentDirectory.name; //Explicit call to ostream insertion to 
                                        //avoid confusion with ofstream
  os << currentDirectory.time;
  os << (char) ' ';
  os << currentDirectory.permissions;
  os << (char) ' ';
  os << currentDirectory.subDirectoryCount << endl;
  for (int i = 0; i < currentDirectory.subDirectoryCount; i++)
    os << *(currentDirectory.subDirectories[i]);
  return os;
}

ostream& operator<<(ostream &os, const Directory &currentDirectory)
{
  os << currentDirectory.permissions << currentDirectory.time << " " 
    << currentDirectory.name << endl;
  return os;
}


ifstream& operator>>(ifstream &is, Directory **currentDirectory)
{
  char name[80];
  is >> name;
  *(currentDirectory) = new Directory(name);
  is >> (*currentDirectory)->time;
  is >> (*currentDirectory)->permissions;
  is >> (*currentDirectory)->subDirectoryCount;
  for (int i = 0; i < (*currentDirectory)->subDirectoryCount; i++)
  {
    is >> &((*currentDirectory)->subDirectories[i]);
    (*currentDirectory)->subDirectories[i]->parent = *currentDirectory;
  }
  return is;
}