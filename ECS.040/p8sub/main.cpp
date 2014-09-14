//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <fstream>
#include "SVector.h"

using namespace std;


int main(int argc, char *argv[])
{
  int size;
  SVector<int> *svp;
  ifstream inf(argv[1]);
  inf >> size;
  try
  {
    svp = new SVector<int>(size);
  
    string index;
    int value;
    while (inf)
    {
      int isgood = 1;
      switch (inf.get())
      {
        case 'U' :
          inf >> value;
          inf >> index;
          inf.ignore();
          try
          {
            svp->push_back(index, value);
          }
          catch (Whoops e)
          {
            cerr << "Duplicated index: " << e.what() << endl;
          }
          break;
        case 'A' :
          inf >> index;
          inf.ignore();
          try
          {
            value = (*svp)[index];
          }
          catch (range_error e)
          {
            cerr << "Range error: " << e.what() << endl;
            isgood = 0;
          }
          if (isgood)
            cout << "Access value: " << value << endl;
          break;
        case 'O' :
          inf.ignore();
          try
          {
            svp->pop_back();
          }
          catch (underflow_error e)
          {
            cerr << e.what() << endl;
          }
          break;
      }
    }
  }
  catch (bad_alloc e)
  {
    cerr << e.what() << endl;
  }
  inf.close();
} // main()