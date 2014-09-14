// Author: Sean Davis

#include <iostream>
#include "permissions.h"
using namespace std;

void Permissions::print() const
{
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
} // print()

void Permissions::set(short originalPermissions,  short umask)
{
  octal = originalPermissions & ~umask;
} // setPermissions()
