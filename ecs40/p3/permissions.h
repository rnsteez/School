//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef PERMISSIONS_H
	#define PERMISSIONS_H

class Permissions
{
  short octal;
  
public:
  void print() const;
  void set(short originalPermissions, short umask);
};

#endif

