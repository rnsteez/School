// Author: Sean Davis

#ifndef DIRECTORY_H
	#define DIRECTORY_H

#include "permissions.h"
#include "Time.h"
#define MAX_DIRECTORIES 3

class Directory
{
  char *name;
  Directory *subDirectories[MAX_DIRECTORIES];
  Time modificationTime;
  int subDirectoryCount;
  Permissions permissions;
  Directory *parent;
public:
  Directory(const char *name, short umask  = 0, Directory *parent = NULL);
  Directory(const Directory &rhs);
  ~Directory();
  Directory* cd(int argCount, const char *arguments[]);
  void chmod( int argCount, const char *arguments[]);
  void cp( int argCount, const char *arguments[]);
  void ls(int argCount, const char *arguments[]) const;
  void mkdir(int argCount, const char *arguments[], short umask);
  void showPath() const;
  bool operator== (const Directory &rhs) const;
  friend ostream& operator<< (ostream &os, const Directory &directory);
  friend istream& operator>> (istream &is, Directory &directory);

}; // class Directory
#endif

