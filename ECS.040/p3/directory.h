//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef DIRECTORY_H
	#define DIRECTORY_H

#include "permissions.h"
#include <cstring>
#define MAX_DIRECTORIES 3

class Directory
{
  char *name;
  Directory *subDirectories[MAX_DIRECTORIES];
  int time;
  int subDirectoryCount;
  Permissions permissions;
  Directory *parent;
  
public:
  Directory* cd(int argCount, const char *arguments[]);
  void ls(int argCount, const char *arguments[]) const;
  void mkdir(int argCount, const char *arguments[], short umask, int time);
  void showPath() const;
  
  Directory(const char *dname, short umask, int time, Directory *parent);
  
  ~Directory();
  
};

#endif

