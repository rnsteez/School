//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include "songs.h"

using namespace std;

istream& operator>> (istream &is, Song &song)
{
  string s;
  bool isNewName = 0;
  getline(is, s, '_');
  if (s.find("A ") == 0)
  {
    s = s.erase(0, 2);
    s += ", A";
  }
  else if (s.find("THE ") == 0)
  {
    s = s.erase(0, 4);
    s += ", THE";
  }
  song.title = s;
  is.ignore(2);
  getline(is, s, '_');
  for (string::iterator itr = ++s.begin(); itr != s.end(); itr++)
  {
    if ((*itr >= 'A' && *itr <= 'Z'))
    {
      if(!isNewName)
      {
        *itr -= ('Z' - 'z');
      }
      isNewName = 0;
    }
    else // next char might be new name
      isNewName = 1;
  }
  song.artist = s;
  is.ignore(2);
  getline(is, s, '_');
  is.ignore(2);
  getline(is, s, '\n');
  if (s.find("CD+G") != string::npos)
    s = s.erase(s.find("CD+G"));
  song.album = s;
  
  return is;
} // operator>>()


ostream& operator<< (ostream &os, Song &song)
{
  cout << song.title << ":" << song.artist << ":" << song.album << endl;
  return os;
} // operator<<()