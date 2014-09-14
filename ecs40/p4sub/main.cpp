//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include "funix.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	Funix *funix = new Funix();
  funix->run();
  delete funix;
} // main()
