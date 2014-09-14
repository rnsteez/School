//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include <stdlib.h>
#include "funix.h"

int main()
{
	Funix *funix = new Funix();
  funix->run();
  delete funix;
} // main()
