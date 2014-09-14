//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef TimeH
#define TimeH

#include <ctime>
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
