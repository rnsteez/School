//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef DIRECTORY_H
	#define DIRECTORY_H

#include "file.h"
#include "linkedlist.h"
template <class T>
class LinkedList;

class Directory: public File
{
  LinkedList<File> subDirectories;
  int subDirectoryCount;
  Directory *parent;
public:
  Directory(const char *nam, Directory *paren = NULL, const char *owner = NULL);
  Directory(const Directory &rhs);
  Directory* cd(int argCount, const char *arguments[], const char *user);
  void chmod( int argCount, const char *arguments[], const char *user);
  void chown( int argCount, const char *arguments[], const char *user);

  void cp( int argCount, const char *arguments[], const char *user);
  void ls(int argCount, const char *arguments[], const char *user) const;
  void mkdir(int argCount, const char *arguments[], const char *user);
  void touch(int argCount, const char *arguments[], const char *user);
  void showPath() const;
  ostream& write(ostream &os, const Directory &directory) const;
  friend ostream& operator<< (ostream &os, const Directory &directory);
  friend istream& operator>> (istream &is, Directory &directory);

}; // class Directory
#endif

