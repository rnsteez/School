//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <iostream>
#include "permissions.h"
#include <cstring>
using namespace std;
  


ostream& operator<<(ostream& os, const Permissions &per)
{
  short n = per.octal/100;
  short n2 = (per.octal - (n * 100)) / 10;
  short n3 = (per.octal - ((n * 100) + (n2 * 10)));
  
  
  if(n & 4)
    os << "r";
  else // 4-bit not set
    os << "-";    
  if(n & 2)
    os << "w";
  else // 2-bit not set            
    os << "-";                   
  if(n & 1)                    
    os << "x";                   
  else // 1-bit not set            
    os << "-";
  
  if(n2 & 4)
    os << "r";
  else // 4-bit not set
    os << "-";    
  if(n2 & 2)
    os << "w";
  else // 2-bit not set            
    os << "-";                   
  if(n2 & 1)                    
    os << "x";                   
  else // 1-bit not set            
    os << "-";
  
  if(n3 & 4)
    os << "r";
  else // 4-bit not set
    os << "-";    
  if(n3 & 2)
    os << "w";
  else // 2-bit not set            
    os << "-";                   
  if(n3 & 1)                    
    os << "x";                   
  else // 1-bit not set            
    os << "-";
  
  return os;
}


ofstream& operator<<(ofstream& os, const Permissions &per)
{
    os << per.octal;
    return os;
}

ifstream& operator>>(ifstream& is, Permissions &per)
{
  is >> per.octal;
  return is;
}

void Permissions::set(Permissions &umask)
{
  short n = umask.octal/100;
  short n2 = (umask.octal - (n * 100)) / 10;
  short n3 = (umask.octal - ((n * 100) + (n2 * 10)));
  
  octal = (100 * (7 & ~n)) + (10 * (7 & ~n2)) + (7 & ~n3);
} // Permissions.set()

void Permissions::chmod(short oct)
{
  octal = oct;
}
