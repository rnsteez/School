//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef FILE_H
  #define	FILE_H

#include "permissions.h"
#include "Time.h"

class File
{
  char* name;
  Permissions permissions;
  Time modificationTime;
public:
  File(const char *name, Permissions perm = Permissions(0666));
  File(const File &rhs);
  virtual ~File();
  bool checkPermissions(short perm, const char *user) const;
  void changePermissions(short perm);
  const char* getOwner() const;
  void chown(const char *owner);
  void print() const;
  void rename(const char *nam);
  const char* showName() const;
  void timeUpdate();
  bool isFile() const;
  virtual File* touch(const char *name, const char *user);
  bool operator== (const File &rhs) const;
  bool operator< (const File &rhs) const;
  virtual ostream& write(ostream &os, const File &file) const;
  friend ostream& operator<< (ostream &os, const File &file);
  friend istream& operator>> (istream &is, File &file);
}; // class File


#endif	/* FILE_H */

