//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef SONGS_H
	#define SONGS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Song
{
  string title;
  string artist;
  string album;
public:
  friend void searchArtist(vector<Song> &songs);
  friend void searchTitle(vector<Song> &songs);
  friend void searchAlbum(vector<Song> &songs);
  friend void searchPhrase(vector<Song> &songs);
  friend void sort(vector<Song> &songs, const string type);
  friend istream& operator>> (istream &is, Song &song);
  friend ostream& operator<< (ostream &os, Song &song);
}; // class Song

#endif // SONGS_H

