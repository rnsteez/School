//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <iostream>
#include <iomanip>
#include <cstring>
#include "permissions.h"
using namespace std;

short Permissions::umask = 022;

Permissions::Permissions(short originalPermissions, const char *owne)
{
  value = originalPermissions & ~umask;

  if(owne)
  {
    owner = new char[strlen(owne) + 1];
    strcpy(owner, owne);
  } // if owne not NULL
  else // owne == NULL
    owner = NULL;
} // Permissions()


Permissions::Permissions(const Permissions &rhs) : value(rhs.value)
{
  if(rhs.owner)
  {
    owner = new char[strlen(rhs.owner) + 1];
    strcpy(owner, rhs.owner);
  } // if rhs has non-NULL owner
  else // rhs.owner == NULL
    owner = NULL;
}  // Permissions()


Permissions::~Permissions()
{
  if(owner)
    delete owner;
}  // ~Permissions()


bool Permissions::check(short permissions, const char *user) const
{
  if(strcmp(user, owner)) // different user from owner
    return ((value & 7) & permissions)  == permissions;

  return (((value >> 6) & 7) & permissions) == permissions;
}  // check()


void Permissions::chmod(short permissions)
{
  short temp = value;
  value = permissions;
  value += (temp >> 9) * 01000;
} // chmod()


const char* Permissions::getOwner() const
{
  return owner;
} // getOwner()


void Permissions::print() const
{
  if (value >> 9)
    cout << "d";
  else // not a directory
    cout << "-";
  
  for(int i = 6; i >= 0; i -= 3)
  {
    short octal = (value >> i) & 7;

    if(octal & 4)
      cout << "r";
    else // octal & 4 == 0
      cout << "-";

    if(octal & 2)
      cout << "w";
    else  // 2 bit cleared
      cout << "-";

    if(octal & 1)
      cout << "x";
    else  // 1 bit clear
      cout << "-";
  } // for each set of triplets

  cout << ' ' << setw(10) << owner << ' ';
} // print()


void Permissions::readUmask(istream &is)
{
  is >> oct >> umask;
  is.ignore();
} // readUmask()


void Permissions::setOwner(const char *owne)
{
  if(owner)
    delete owner;

  if(owne)
  {
    owner = new char [strlen(owne) + 1];
    strcpy(owner, owne);
  } // if owne is not NULL
  else // owne == NULL
    owner = NULL;
} // setOwner()


void Permissions::setUmask( int argCount, const char *arguments[])
{
  short octal = 0;

  if(argCount != 2)
  {
    cout << "usage: umask octal\n";
    return;
  } // if not 2 arguments

  for(int i = 0; arguments[1][i]; i++)
    if(!isdigit(arguments[1][i]) || arguments[1][i] == '9' || arguments[1][i] == '8')
    {
      cout << "usage: umask octal\n";
      return;
    } // if not octal digit
    else
      octal = octal * 8 + arguments[1][i] - '0';


  if(octal < 0 || octal > 0777)
  {
    cout << "umask: octal must be between 0 and 777\n";
    return;
  } // if octal invalid

  umask = octal;
} // setUmask()


void Permissions::writeUmask(ostream & os)
{
  os << oct << umask << endl;
} // writeUmask()


bool Permissions::isFile() const
{
  return !(value >> 9);
}// is file


ostream& operator<< (ostream & os, const Permissions &permissions)
{
  os << oct << permissions.value << ' ' << permissions.owner << ' ';
  return os;
} // operator<<


istream& operator>> (istream & is, Permissions &permissions)
{
  char s[256];
  is >> oct >> permissions.value >> s;
  is.ignore();
  permissions.owner = new char[strlen(s) + 1];
  strcpy(permissions.owner, s);
  return is;
} // operator>>
