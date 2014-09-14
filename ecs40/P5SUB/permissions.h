//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef PERMISSIONS_H
    #define PERMISSIONS_H

#include <iostream>
using namespace std;

class Permissions
{
  short value;
  static short umask;
  char* owner;
public:
  Permissions();
  void setOwner(const char *newOwner);
  int check(const char *user) const;
  bool checkOwn(const char* user) const;
  void print() const;
  static void setUmask (short newUmask);
  static short getUmask ();
  void chmod(int octal);
  void set(short originalPermissions);
  friend ostream& operator<< (ostream &os, const Permissions &permissions);
  friend istream& operator>> (istream &is, Permissions &permissions);
};  // class Permissions

#endif
