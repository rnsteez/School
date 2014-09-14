// Author: Sean Davis
#ifndef PERMISSIONS_H
	#define PERMISSIONS_H

#include <iostream>
using namespace std;

class Permissions
{
  short value;
public:
  void print() const;
  void set(short originalPermissions, short umask);
  friend ostream& operator<< (ostream & os, const Permissions &permissions);
  friend istream& operator>> (istream & is, Permissions &permissions);
};  // class Permissions

#endif

