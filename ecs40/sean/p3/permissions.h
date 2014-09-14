// Author: Sean Davis
#ifndef PERMISSIONS_H
	#define PERMISSIONS_H

class Permissions
{
  short octal;
public:
  void print() const;
  void set(short originalPermissions, short umask);
};  // class Permissions

#endif

