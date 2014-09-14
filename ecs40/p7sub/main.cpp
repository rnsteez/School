//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <fstream>
#include <vector>
#include "songs.h"

using namespace std;

void searchArtist(vector<Song> &songs);
void searchTitle(vector<Song> &songs);
void searchAlbum(vector<Song> &songs);
void searchPhrase(vector<Song> &songs);
void sort(vector<Song> &songs, const string type);

int main()
{
  int choice = 1;
  vector<Song> songs;
  Song song;
  
  ifstream inf("songs.txt");
  while (inf.peek() != EOF)
  {
    inf >> song;
    songs.push_back(song);
  }
  inf.close();
  
  while (choice)
  {
    cout << endl << "Song Menu\n" << "0. Done.\n" << "1. Search for Artist.\n" 
      << "2. Search for Title.\n" << "3. Search for Album.\n" 
      << "4. Search for title phrase.\n" << endl << "Your choice: ";

    cin >> choice;

    switch (choice)
    {
      case 0 : 
        break;
      case 1 : 
        searchArtist(songs);
        break;
      case 2 : 
        searchTitle(songs);
        break;
      case 3 : 
        searchAlbum(songs);
        break;
      case 4 : 
        searchPhrase(songs);
        break;
      default : 
        cout << "Your choice must be between 0 and 4.\nPlease try again.\n";
    }
  }
} // main()


void searchArtist(vector<Song> &songs)
{
  vector<Song> found;
  vector<Song>::iterator itr;
  string text;
  cout << "Please enter the artist's name: ";
  cin.ignore();
  getline(cin, text);
  for (itr = songs.begin(); itr != songs.end(); itr++)
  {
    if (itr->artist == text)
      found.push_back(*itr);
  }
  
  sort(found, "Title");
  
  for (itr = found.begin(); itr != found.end(); itr++)
  {
    cout << *itr;
  }
} // searchArtist()


void searchTitle(vector<Song> &songs)
{
  vector<Song> found;
  vector<Song>::iterator itr;
  string text;
  cout << "Please enter the title: ";
  cin.ignore();
  getline(cin, text);
  for (itr = songs.begin(); itr != songs.end(); itr++)
  {
    if (itr->title == text)
      found.push_back(*itr);
  }
  
  sort(found, "Artist");
  
  for (itr = found.begin(); itr != found.end(); itr++)
  {
    cout << *itr;
  }
} // searchTitle()


void searchAlbum(vector<Song> &songs)
{
  vector<Song> found;
  vector<Song>::iterator itr;
  string text;
  cout << "Please enter the album: ";
  cin.ignore();
  getline(cin, text);
  for (itr = songs.begin(); itr != songs.end(); itr++)
  {
    if (itr->album == text)
      found.push_back(*itr);
  }
  
  sort(found, "Title");
  
  for (itr = found.begin(); itr != found.end(); itr++)
  {
    cout << *itr;
  }
  
} // searchAlbum()


void searchPhrase(vector<Song> &songs)
{
  vector<Song> found;
  vector<Song>::iterator itr;
  string text;
  cout << "Please enter the phrase: ";
  cin.ignore();
  getline(cin, text);
  for (itr = songs.begin(); itr != songs.end(); itr++)
  {
    if (itr->title.find(text) != string::npos)
      found.push_back(*itr);
  }
  
  sort(found, "Artist");
  
  for (itr = found.begin(); itr != found.end(); itr++)
  {
    cout << *itr;
  }
} // searchPhrase()


void sort(vector<Song> &songs, const string type)
{
  vector<Song>::iterator itr, current, prev;
  
  if (type == "Title")
  {
    for (itr = songs.begin(); itr != songs.end(); itr++)
    {
      for (current = itr; current != songs.begin(); current--)
      {
        prev = current;
        prev--;
        if (current->title < prev->title)
        {
          prev->title.swap(current->title);
          prev->artist.swap(current->artist);
          prev->album.swap(current->album);
        }
        else // correct position
          break;
      }
    }
  }
  
  else if (type == "Artist")
  {
    for (itr = songs.begin(); itr != songs.end(); itr++)
    {
      for (current = itr; current != songs.begin(); current--)
      {
        prev = current;
        prev--;
        if (current->artist < prev->artist)
        {
          prev->title.swap(current->title);
          prev->artist.swap(current->artist);
          prev->album.swap(current->album);
        }
        else // correct position
          break;
      }
    }
  }
} // sort()