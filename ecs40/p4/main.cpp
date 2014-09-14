// Author: Sean Davis

#include <stdlib.h>
#include "funix.h"

int main()
{
	Funix *funix = new Funix();
  funix->run();
  delete funix;
} // main()
