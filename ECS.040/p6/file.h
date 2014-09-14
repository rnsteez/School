// Author: Sean Davis
#ifndef fileH
#define fileH

#include "Time.h"
#include "permissions.h"

class File
{
  char *name;
  Time modificationTime;
  Permissions permissions;
protected:
  virtual ostream& write(ostream& os) const;
public:
  File(const char *nam,  const Permissions &perm = Permissions(00666, NULL));
  File(const File &rhs);
  virtual ~File();
  void changePermissions(short perms);
  bool checkPermissions(short perms, const char *user) const;
  void chown(const char *owner);
  bool isFile() const;
  void print(bool longFormat) const;
  void rename(const char *nam);
  void showName() const;
  void touch();
  bool operator== (const File &rhs) const;
  bool operator< (const File &rhs) const;
  friend ostream& operator<< (ostream &os, const File &file);
  friend istream& operator>> (istream &is, File &file);

}; // File class




#endif
