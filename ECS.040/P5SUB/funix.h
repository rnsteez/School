//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef FUNIX_H
  #define FUNIX_H

#include <iostream>
#include "directory.h"

using namespace std;

class Funix
{
  Directory *currentDirectory;
  void cd( int argCount, const char *arguments[]);
  // calls cd() with currentDirectory as one of its parameters
  void chmod( int argCount, const char *arguments[]);
  void cp( int argCount, const char *arguments[]);
  int eXit( int argCount, const char *arguments[]);
  // checks "exit" command, returns 0 on proper exit
  void getCommand( char *command); // writes prompt and reads command
   void ls( int argCount, const char *arguments[]);
  // calls ls() with currentDirectory as one of its parameters
  void mkdir( int argCount, const char *arguments[]);
  // calls mkdir() with currentDirectory as one of its parameters
  int processCommand( char *command); // returns 0 on proper exit
  void setUmask( int argCount, const char *arguments[]);
  // checks "umask" command and executes it if it is proper
  void writePrompt(); // shows path and '+'
  void su(int argCount, const char *arguments[]);
  void chown(int argCount, const char *arguments[]);
  friend istream& operator>> (istream &is, Funix &f);
  friend ostream& operator<< (ostream &is, Funix &f);
public:
  static char* user;
  Funix(); // creates currentDirectory, and sets umask and time
  ~Funix();
  void run(); // reads and processes commands until proper exit

}; // Funix class
#endif

