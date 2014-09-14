#ifndef TimeH
#define TimeH

#include <ctime>
#include <iostream>
using namespace std;

class Time
{
  short month;
  short day;
  short hour;
  short minute;
  short second;
public:
  Time();
  void update();
  void print()const;
  friend ostream& operator<< (ostream &os, const Time &t);
  friend istream& operator>> (istream &is, Time &t);
}; // class Time

#endif
