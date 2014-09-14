//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef PERMISSIONS_H
	#define PERMISSIONS_H

#include <iostream>
#include <fstream>
using namespace std;

class Permissions
{
  short octal;
public:
  friend ofstream& operator<<(ofstream& os, const Permissions &per);
  friend ostream& operator<<(ostream& os, const Permissions &per);
  friend ifstream& operator>>(ifstream& is, Permissions &per);
  void set(Permissions &umask);
  void chmod(short oct);
};  // class Permissions

#endif

