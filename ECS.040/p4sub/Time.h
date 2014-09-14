//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef TIME_H
  #define TIME_H

#include <iostream>
#include <ctime>
using namespace std;

class Time
{
  struct tm tim;
public:
    Time(); 
    friend ofstream& operator<<(ofstream &os, const Time &T);
    friend ifstream& operator>>(ifstream &is, Time &T);
    friend ostream& operator<<(ostream &os, const Time &T);
};//class Time

#endif