#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include "song.h"

using namespace std;

void Song::adjust()
{
  if(title.find("A ") == 0)
    title = title.substr(2) + ", A";

  if(title.find("THE ") == 0)
    title = title.substr(4) + ", THE";

  bool begin = true;
  for(string::iterator itr = artist.begin(); itr != artist.end(); itr++)
  {
    if(!isalpha(*itr))
      begin = true;

    if(!begin)
      *itr = tolower(*itr);

    if(begin && isalpha(*itr))
      begin = false;
  }

  unsigned int pos = album.find("CD+G");
  if(pos != string::npos)
    album.erase(pos - 1);

} // adjust()


const string& Song::getArtist()const
{
  return artist;
} // getArtist()


const string& Song::getAlbum()const
{
  return album;
} // getAlbum()


const string& Song::getTitle()const
{
  return title;
} // getTitle()

void Song::swap(Song &song)
{
  title.swap(song.title);
  artist.swap(song.artist);
  album.swap(song.album);
}

ostream& operator<< (ostream &os, const Song &s)
{
  os << s.title << ":" << s.artist << ":"  << s.album << endl;

  return os;
} // operator <<

istream& operator>> (istream &is, Song &s)
{
  string code;

  getline(is, s.title, '_');

  for(int i = 0; i < 2; i++)
    is.ignore(1,'_');

  getline(is, s.artist, '_');

  for(int i = 0; i < 2; i++)
    is.ignore(1,'_');

  getline(is, code, '_');

  for(int i = 0; i < 2; i++)
    is.ignore(1,'_');

  getline(is, s.album);

  return is;
}


