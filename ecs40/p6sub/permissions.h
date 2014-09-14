//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef PERMISSIONS_H
	#define PERMISSIONS_H

#include <iostream>
using namespace std;

class Permissions
{
  short value;
  static short umask;
  char *owner;
public:
  Permissions(short originalPermissions, const char *owne = NULL);
  Permissions(const Permissions &p);
  ~Permissions();
  bool check(short permissions, const char *user) const;
  void chmod(short permissions);
  const char* getOwner() const;
  void print() const;
  static void readUmask(istream &is);
  void setOwner(const char *owne);
  static void setUmask( int argCount, const char *arguments[]);
  static void writeUmask(ostream &os);
  bool isFile() const;
  friend ostream& operator<< (ostream & os, const Permissions &permissions);
  friend istream& operator>> (istream & is, Permissions &permissions);
};  // class Permissions

#endif

