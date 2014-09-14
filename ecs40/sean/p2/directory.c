// Author: Sean Davis
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "directory.h"

Directory* cd(Directory *currentDirectory, int argCount, const char *arguments[])
{
  if(argCount != 2)
  {
    printf("usage: cd directoryName\n");
    return currentDirectory;
  } // if wrong number of arguments

  if(strcmp(arguments[1], "..") == 0)
  {
    if(currentDirectory->parent)
      return currentDirectory->parent;
    else
      return currentDirectory;
  } // if cd ..

  for(int i = 0; i < currentDirectory->subDirectoryCount; i++)
    if(strcmp(arguments[1], currentDirectory->subDirectories[i]->name) == 0)
      return currentDirectory->subDirectories[i];

  printf("%s: no such directory\n", arguments[1]);
  return currentDirectory;

} // cd()


void createDirectory(Directory *directory, const char *name, short umask,
  int time, Directory *parent)
{
  directory->name = (char*) malloc(strlen(name) + 1);
  strcpy(directory->name, name);
  setPermissions(&directory->permissions, 7, umask);
  directory->time = time;
  directory->parent = parent;
  directory->subDirectoryCount = 0;
} // createDirectory()


void ls(Directory *directory, int argCount, const char *arguments[])
{
  if(argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l")))
  {
    printf("usage: ls [-l]\n");
    return;
  }  // if 

  if(directory->subDirectoryCount == 0)
    return;
    
  if(argCount == 2) // must be ls -l
  {
   for(int i = 0; i < directory->subDirectoryCount; i++)
   {
      print(&directory->subDirectories[i]->permissions);
      printf(" %d %s\n", directory->subDirectories[i]->time,
        directory->subDirectories[i]->name);
    } // for each subdirectory
  } // if -l
  else // simple ls
  {
    for(int i = 0; i < directory->subDirectoryCount; i++)
      printf("%s ", directory->subDirectories[i]->name);

    printf("\n");
  } // else simple else
} // ls()


void mkdir(Directory *currentDirectory, int argCount, const char *arguments[],
  short umask, int time)
{
  if(argCount != 2)
  {
    printf("usage: mkdir directory_name\n");
    return;
  } // if wrong number of arguments

  if(currentDirectory->subDirectoryCount == MAX_DIRECTORIES)
  {
    printf("mkdir: %s already contains the maximum number of directories\n",
      currentDirectory->name);
    return;
  } // if already at max subdirectories

  for(int i = 0; i < currentDirectory->subDirectoryCount; i++)
    if(strcmp(arguments[1], currentDirectory->subDirectories[i]->name) == 0)
    {
      printf("mkdir: cannot create directory '%s': File exists\n", arguments[1]);
      return;
    } // for each sub directory

  currentDirectory->subDirectories[currentDirectory->subDirectoryCount]
    = (Directory*) malloc(sizeof(Directory));

  createDirectory(
    currentDirectory->subDirectories[currentDirectory->subDirectoryCount++],
    arguments[1], umask, time, currentDirectory);
} // mkdir()


void showPath(Directory *directory)
{
  if(directory->parent)
  {
    showPath(directory->parent);
    printf("%s/", directory->name);
  } // if has a parent
  else // directory has no parent, i.e. the root
    printf("%s", directory->name);
} // showPath()


