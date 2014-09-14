//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <iostream>
#include "permissions.h"
using namespace std;


void Permissions::print() const
{
  if(octal & 4)
    cout << "r";
  else // 4-bit not set
    cout << "-";

  if(octal & 2)
    cout << "w";
  else // 2-bit not set
    cout << "-";

  if(octal & 1)
    cout << "x";
  else // 1-bit not set
    cout << "-";
} // Permissions.print()


void Permissions::set(short originalPermissions, short umask)
{
  octal = originalPermissions & ~umask;
} // Permissions.set()