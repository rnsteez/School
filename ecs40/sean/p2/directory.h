// Author: Sean Davis

#ifndef DIRECTORY_H
	#define DIRECTORY_H

#include "permissions.h"
#define MAX_DIRECTORIES 3

typedef struct Dir
{
  char *name;
  struct Dir *subDirectories[MAX_DIRECTORIES];
  int time;
  int subDirectoryCount;
  Permissions permissions;
  struct Dir *parent;
} Directory;

Directory* cd(Directory *currentDirectory, int argCount, const char *arguments[]);
void createDirectory(Directory *directory, const char *name, short umask,
  int time, Directory *parent);
void ls(Directory *directory, int argCount, const char *arguments[]);
void mkdir(Directory *directory, int argCount, const char *arguments[],
  short umask, int time);
void showPath(Directory *directory);

#endif

