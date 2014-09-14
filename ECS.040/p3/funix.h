//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef FUNIX_H
  #define FUNIX_H

#include "directory.h"

class Funix
{
  Directory *currentDirectory;
  int umask;
  int time;
  
  void cd(int argCount, const char *arguments[]);
  // calls cd() with currentDirectory as one of its parameters
  int eXit(int argCount, const char *arguments[]);
  // checks "exit" command, returns 0 on proper exit
  void getCommand(char *command); // writes prompt and reads command
  void init(); // creates currentDirectory, and sets umask and time
  void ls(int argCount, const char *arguments[]) const;
  // calls ls() with currentDirectory as one of its parameters
  void mkdir(int argCount, const char *arguments[]);
  // calls mkdir() with currentDirectory as one of its parameters
  int processCommand(char *command); // returns 0 on proper exit
  void setUmask(int argCount, const char *arguments[]);
  // checks "umask" command and executes it if it is proper
  void writePrompt() const; // shows path and '#'
  
public:
  void run(); // reads and processes commands until proper exit
  
  Funix();
  
  ~Funix();
  
};


#endif

