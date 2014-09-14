//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef DIRECTORY_H
	#define DIRECTORY_H

#include "permissions.h"
#include "Time.h"
#include <iostream>
#define MAX_DIRECTORIES 3
using namespace std;

class Directory
{
  char *name;
  Directory *subDirectories[MAX_DIRECTORIES];
  Time time;
  int subDirectoryCount;
  Permissions permissions;
  Directory *parent;
public:
  Directory(const char *name, Permissions umask, Directory *parent);
  Directory(const char *name);
  ~Directory();
  Directory(const Directory& ori);
  bool operator==(const Directory &rhs) const;
  Directory* cd(int argCount, const char *arguments[]);
  void ls(int argCount, const char *arguments[]) const;
  void mkdir(int argCount, const char *arguments[], Permissions umask);
  void chmod(int argCount, const char *arguments[]);
  // changes permissions of specified files to specified octal
  void showPath() const;
  void cp(int argCount, const char *arguments[]);
  friend ofstream& operator<<(ofstream &os, const Directory &currentDirectory);
  friend ostream& operator<<(ostream &os, const Directory &currentDirectory);
  friend ifstream& operator>>(ifstream &is, Directory **currentDirectory);
}; // class Directory
#endif

