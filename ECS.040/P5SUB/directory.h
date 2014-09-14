//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef DIRECTORY_H
	#define DIRECTORY_H

#include "permissions.h"
#include "Time.h"
#include "linkedlist.h"

class Directory
{
  char *name;
  LinkedList subDirectories;
  Time modificationTime;
  int subDirectoryCount;
  Permissions permissions;
  Directory *parent;
public:
  Directory(const char *name, Directory *parent = NULL);
  Directory(const Directory &rhs);
  ~Directory();
  Directory* cd(int argCount, const char *arguments[], const char *user);
  void chmod(int argCount, const char *arguments[], const char *user);
  void cp( int argCount, const char *arguments[], const char *user);
  void ls(int argCount, const char *arguments[], const char *user) const;
  void mkdir(int argCount, const char *arguments[], const char *user);
  void showPath() const;
  void chown(int argCount, const char *arguments[]);
  bool operator== (const Directory &rhs) const;
  bool operator< (const Directory &rhs) const;
  friend ostream& operator<< (ostream &os, const Directory &directory);
  friend istream& operator>> (istream &is, Directory &directory);

}; // class Directory
#endif

