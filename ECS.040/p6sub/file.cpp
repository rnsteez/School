//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <cstring>
#include "file.h"

using namespace std;

File::File(const char *nam, Permissions perm) : permissions(perm)
 {
   name = new char[strlen(nam) + 1];
   strcpy(name, nam);
   modificationTime.update();
 } // File()
 
 
File::File(const File &rhs) : permissions(rhs.permissions)
 {
   name = new char[strlen(rhs.name) + 1];
   strcpy(name, rhs.name);
 }//file copy constructor

 
File::~File()
{
  delete [] name;
} // ~File()


bool File::checkPermissions(short perm, const char *user) const
{
  return permissions.check(perm, user);
} // checkPermissions()


void File::changePermissions(short perm)
{
  permissions.chmod(perm);
} // changePermissions()


const char* File::getOwner() const
{
  return permissions.getOwner();
} // getOwner()


void File::chown(const char *owner)
{
  permissions.setOwner(owner);
} // chown()


void File::print() const
{
  permissions.print();
  cout << " ";
  modificationTime.print();
} // print()


void File::rename(const char *nam)
{
  if (name)
    delete [] name;
  
  name = new char[strlen(name) + 1];
  strcpy(name, nam);
} // rename()


const char* File::showName() const
{
  return name;
} // showName()


void File::timeUpdate()
{
  modificationTime.update();
} // timeUpdate()


bool File::isFile() const
{
  return permissions.isFile();
} // isFile()


File* File::touch(const char *name, const char *user)
{
  return new File(name, Permissions(0666, user));
} // touch()


bool File::operator== (const File &rhs) const
{
  return !strcmp(name, rhs.name);
} // operator==


bool File::operator< (const File &rhs) const
{
  return strcmp(name, rhs.name) < 0;
} // operator<
 

ostream& File::write(ostream &os, const File &file) const
{
  os << 'F';
  os << file.name << ' ' <<  file.modificationTime << file.permissions << endl;

  return os;
} // write()


ostream& operator<< (ostream &os, const File &file)
{
  file.write(os, file);
  return os;
} // operator<<()


istream& operator>> (istream &is, File &file)
{
  char temp[80];
  is >> temp;
 
  file.rename(temp);
  
  is.ignore();  // eat space char
  is >> file.modificationTime >> file.permissions;
  
  return is;
} // operator>>()