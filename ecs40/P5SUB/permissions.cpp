//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <iostream>
#include <iomanip>
#include <cstring>
#include "permissions.h"
#include "directory.h"
#include "funix.h"
using namespace std;
  


short Permissions::umask = 022;



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
  
  cout << setw (10) << right << owner << ' ';
} // print()

 void Permissions::setUmask (short newUmask)
{
  if (umask)
  {
    umask = newUmask;
  }
}//set Umask

 
short Permissions::getUmask ()
{
  return umask;
} // getUmask()
 

void Permissions::chmod(int octal)
{
  value = octal;
} // chmod


void Permissions::set(short originalPermissions)
{
  value = originalPermissions & ~umask;
} // set


Permissions::Permissions()
{
  owner = new char[80];
  strcpy(owner, Funix::user);
}//permissions constructor (seriously can anyone hear me?)


void Permissions::setOwner(const char *newOwner)
{ 
  strcpy(owner, newOwner);
}//set the owner (allergies suck)


int Permissions::check(const char *user) const
{
  if (!strcmp(user, owner))
    return (value / 0100);
  else // owner is not user
    return (value & 7);
} // check


bool Permissions::checkOwn(const char* user) const
{
  if (!strcmp(user, owner))
    return 1;
  else // owner is not user
    return 0;
}
 

ostream& operator<< (ostream & os, const Permissions &permissions)
{
  os << oct << permissions.value << ' ' << dec << permissions.owner << ' ';
  return os;
} // operator<<


istream& operator>> (istream & is, Permissions &permissions)
{
   is >> oct >> permissions.value >> dec >> permissions.owner;
   is.ignore();
   return is;
} // operator>>