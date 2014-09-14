// Author: Sean Davis

#ifndef DIRECTORY_H
	#define DIRECTORY_H

#include "linkedlist.h"
#include "file.h"

class Directory : public File
{

  LinkedList <File> subDirectories;
  int subDirectoryCount;
  Directory *parent;
public:
  Directory(const char *name, Directory *parent = NULL, const char *owner = NULL);
  Directory(const Directory &rhs);
  Directory* cd(int argCount, const char *arguments[], const char *user);
  void chmod( int argCount, const char *arguments[], const char *user);
  void chown( int argCount, const char *arguments[], const char *user);
  void cp( int argCount, const char *arguments[], const char *user);
  void ls(int argCount, const char *arguments[], const char *user) const;
  void mkdir(int argCount, const char *arguments[], const char *user);
  void showPath() const;
  void touch(int argCount, const char *arguments[], const char *user);
  ostream& write(ostream &os) const;
  friend istream& operator>> (istream &is, Directory &directory);
}; // class Directory
#endif

