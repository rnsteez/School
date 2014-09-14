// Author: Sean Davis

#include <iostream>
#include "permissions.h"
using namespace std;

void Permissions::print() const
{
  for(int i = 6; i >= 0; i -= 3)
  {
    short octal = (value >> i) & 7;

    if(octal & 4)
      cout << "r";
    else
      cout << "-";

    if(octal & 2)
      cout << "w";
    else
      cout << "-";

    if(octal & 1)
      cout << "x";
    else
      cout << "-";
  } // for each octal triplet
} // print()


void Permissions::set(short originalPermissions,  short umask)
{
  value = originalPermissions & ~umask;
} // set()


ostream& operator<< (ostream & os, const Permissions &permissions)
{
  os << oct << permissions.value << ' ' << dec ;
  return os;
} // operator<<


istream& operator>> (istream & is, Permissions &permissions)
{
   is >> oct >> permissions.value >> dec;
   is.ignore();
   return is;
} // operator>>
