// Author: Sean Davis
#include <cstring>
#include "file.h"

File::File(const char *nam,  const Permissions &perm) : permissions(perm)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
} // File()


File::File(const File &rhs) :  permissions(rhs.permissions)
{
  name = new char[strlen(rhs.name)];
  strcpy(name, rhs.name);
} // File copy constructor

File::~File()
{
  delete [] name;
} // ~Directory()

void File::changePermissions(short perms)
{
  permissions.chmod(perms);
} // changePermissions()



bool File::checkPermissions(short perms, const char *user) const
{
  return permissions.check(perms, user);
} // checkPermissions()


void File::chown(const char *owner)
{
  permissions.setOwner(owner);
}

bool File::isFile() const
{
  return permissions.isFile();
} // isFile()

void File::print(bool longFormat) const
{
  if(longFormat)
  {
    permissions.print();
    cout << " ";
    modificationTime.print();
    cout << ' ' << name << endl;
  } // if long format
  else
    cout << name << " ";
} // print()


void File::rename(const char *nam)
{
  if(name)
   delete name;

  if(nam)
  {
    name = new char[strlen(nam) + 1];
    strcpy(name, nam);
  } // if nam is non-NULL
  else
    name = NULL;
} // rename()


void File::showName() const
{
  cout << name;
} // showName()


void File::touch()
{
  modificationTime.update();
}  // touch()

ostream& File::write(ostream &os) const
{
 os << 'F' << name << ' ' <<  modificationTime << permissions << endl;
 return os;
} // print()


bool File::operator== (const File &rhs) const
{
  return !strcmp(name, rhs.name);
} // operator==


bool File::operator< (const File &rhs) const
{
  return strcmp(name, rhs.name) < 0;
} // operator<


ostream& operator<< (ostream &os, const File &file)
{
  return file.write(os);

}  // operator<<


istream& operator>> (istream &is, File &file)
{
  char name[80];
  if(file.name)
    delete [] file.name;

  is >> name;
  file.name = new char[strlen(name) + 1];
  strcpy(file.name, name);
  is.ignore();  // eat space char
  is >> file.modificationTime >> file.permissions;
  is.ignore(); // eat endl
  return is;
}  // operator<<
