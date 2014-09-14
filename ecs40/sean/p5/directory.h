// Author: Sean Davis

#ifndef DIRECTORY_H
	#define DIRECTORY_H

#include "permissions.h"
#include "Time.h"
#include "linkedlist.h"
class LinkedList;

class Directory
{
  char *name;
  LinkedList subDirectories;
  Time modificationTime;
  int subDirectoryCount;
  Permissions permissions;
  Directory *parent;
public:
  Directory(const char *name, Directory *parent = NULL, const char *owner = NULL);
  Directory(const Directory &rhs);
  ~Directory();
  Directory* cd(int argCount, const char *arguments[], const char *user);
  void chmod( int argCount, const char *arguments[], const char *user);
  void chown( int argCount, const char *arguments[], const char *user);

  void cp( int argCount, const char *arguments[], const char *user);
  void ls(int argCount, const char *arguments[], const char *user) const;
  void mkdir(int argCount, const char *arguments[], const char *user);
  void showPath() const;
  bool operator== (const Directory &rhs) const;
  bool operator< (const Directory &rhs) const;
  friend ostream& operator<< (ostream &os, const Directory &directory);
  friend istream& operator>> (istream &is, Directory &directory);

}; // class Directory
#endif

