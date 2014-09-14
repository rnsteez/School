// Author: Sean Davis

#ifndef DIRECTORY_H
	#define DIRECTORY_H

#include "permissions.h"
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
  Directory(const char *name, short umask, int time, Directory *parent);
  ~Directory();
  Directory* cd(int argCount, const char *arguments[]);
  void ls(int argCount, const char *arguments[]) const;
  void mkdir(int argCount, const char *arguments[], short umask, int time);
  void showPath() const;
}; // class Directory
#endif

