#include <vector>
// Author: Sean Davis
#include <fstream>
#include "song.h"

using namespace std;

void titleSort(vector <Song> &found);


void albumSearch(const vector <Song> &songs)
{
  vector <Song> found;
  string album;

  cout << "Please enter the album: ";
  getline(cin, album);

  for(vector<Song>::const_iterator itr = songs.begin(); itr != songs.end(); itr++)
    if(itr->getAlbum() == album)
      found.push_back(*itr);

  titleSort(found);

  for(vector<Song>::const_iterator itr = found.begin(); itr != found.end();
    itr++)
    cout << *itr;
}  // albumSearch()




void artistSearch(const vector <Song> &songs)
{
  vector <Song> found;
  string artist;

  cout << "Please enter the artist's name: ";
  getline(cin, artist);

  for(vector<Song>::const_iterator itr = songs.begin(); itr != songs.end(); itr++)
    if(itr->getArtist() == artist)
      found.push_back(*itr);

  titleSort(found);

  for(vector<Song>::const_iterator itr = found.begin(); itr != found.end();
    itr++)
    cout << *itr;
}  // artistSearch()

void artistSort(vector <Song> &found)
{
  for(vector<Song>::iterator itr = found.begin(); itr != found.end(); itr++)
  {
    vector<Song>::iterator prevItr = itr;
    --prevItr;  

    for(vector<Song>::iterator itr2 = itr; itr2 != found.begin()
      && itr2->getArtist() < prevItr->getArtist(); --itr2, --prevItr)
        itr2->swap(*prevItr);
  } // for each entry
}  // artistSort()


int getChoice()
{
  int choice;

  do
  {
    cout << "\nSong Menu\n0. Done.\n1. Search for Artist.\n2. Search for Title.";
    cout << "\n3. Search for Album.\n4. Search for title phrase.\n\nYour choice: ";
    cin >> choice;
    cin.ignore(1);
    if(choice < 0 || choice > 4)
      cout << "Your choice must be between 0 and 4.\nPlease try again.\n\n";
  } while(choice < 0 || choice > 4);

  return choice;
}  // getChoice()

void readSongs(vector <Song> &songs)
{
  Song song;
  ifstream inf("songs.txt");

  while(inf >> song)
  {
    song.adjust();
    songs.push_back(song);
  }

  inf.close();
} // readSongs

void titleSearch(const vector <Song> &songs)
{
  vector <Song> found;
  string title;

  cout << "Please enter the title: ";
  getline(cin, title);

  for(vector<Song>::const_iterator itr = songs.begin(); itr != songs.end(); itr++)
    if(itr->getTitle() == title)
      found.push_back(*itr);

  artistSort(found);

  for(vector<Song>::const_iterator itr = found.begin(); itr != found.end();
    itr++)
    cout << *itr;
}  // titleSearch()


void titleSort(vector <Song> &found)
{
  for(vector<Song>::iterator itr = found.begin(); itr != found.end(); itr++)
  {
    vector<Song>::iterator prevItr = itr;
    --prevItr;

    for(vector<Song>::iterator itr2 = itr; itr2 != found.begin()
      && itr2->getTitle() < prevItr->getTitle(); --itr2, --prevItr)
        itr2->swap(*prevItr);
  } // for each entry
}  // titleSort()


void wordSearch(const vector <Song> &songs)
{
  vector <Song> found;
  string phrase;

  cout << "Please enter the phrase: ";
  getline(cin, phrase);

  for(vector<Song>::const_iterator itr = songs.begin(); itr != songs.end(); itr++)
    if(itr->getTitle().find(phrase) != string::npos)
      found.push_back(*itr);

  artistSort(found);

  for(vector<Song>::const_iterator itr = found.begin(); itr != found.end();
    itr++)
    cout << *itr;
}  // wordSearchSearch()



int main()
{
  vector <Song> songs;

  readSongs(songs);
  int choice =  getChoice();
  while(choice)
  {
    switch(choice)
    {
      case 1: artistSearch(songs); break;
      case 2: titleSearch(songs); break;
      case 3: albumSearch(songs); break;
      case 4: wordSearch(songs); break;
    } // switch

    choice = getChoice();
  } // while choice not zero


  return 0;
}

