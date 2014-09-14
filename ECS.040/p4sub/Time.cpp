//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <iostream>
#include <fstream>
#include <ctime>
#include "Time.h"
using namespace std;

ofstream& operator<<(ofstream& os, const Time &T)
{
  os << " " << T.tim.tm_mon << " " << T.tim.tm_mday << " " << T.tim.tm_hour 
    << " " << T.tim.tm_min << " " << T.tim.tm_sec;
  return os;
}

ostream& operator<<(ostream &os, const Time &T)
{
  switch(T.tim.tm_mon)
  {
    case 0:
      os << " Jan";
      break;
    case 1:
      os << " Feb";
      break;
    case 2:
      os << " Mar";
      break;
    case 3:
      os << " Apr";
      break;
    case 4:
      os << " May";
      break;
    case 5:
      os << " Jun";
      break;
    case 6:
      os << " Jul";
      break;
    case 7:
      os << " Aug";
      break;
    case 8:
      os << " Sep";
      break;
    case 9:
      os << " Oct";
      break;
    case 10:
      os << " Nov";
      break;
    case 11:
      os << " Dec";
      break;
  }
  os <<"  " << T.tim.tm_mday << " " << T.tim.tm_hour << ":" << T.tim.tm_min 
    << ":" << T.tim.tm_sec;
  return os;
}

ifstream& operator>>(ifstream& is, Time &T)
{
  is >> T.tim.tm_mon >> T.tim.tm_mday >> T.tim.tm_hour >> T.tim.tm_min 
    >> T.tim.tm_sec;
  return is;
}

Time::Time()
{
  time_t rawtime;
  struct tm *tom;
  time(&rawtime);
  tom = localtime(&rawtime);
  tim.tm_mon = tom->tm_mon;
  tim.tm_mday = tom->tm_mday;
  tim.tm_hour = tom->tm_hour;
  tim.tm_min = tom->tm_min;
  tim.tm_sec = tom->tm_sec;
}