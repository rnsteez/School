#ifndef songH
// Author: Sean Davis
#define songH

#include <iostream>
#include <string>
using namespace std;

class Song
{
  string title;
  string code;
  string album;
  string artist;
public:
  void adjust();
  const string& getArtist()const;
  const string& getAlbum()const;
  const string& getTitle()const;
  void swap(Song &song);
  friend istream& operator>> (istream &is, Song & s);
  friend ostream& operator<< (ostream &os, const Song &s);
}; // class Song

//---------------------------------------------------------------------------
#endif
