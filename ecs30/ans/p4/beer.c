// Author: Sean Davis
#include <stdio.h>
#define PIELS 1
#define COORS 2
#define BUD 3
#define IRON_CITY 4

int main(int argc, char *argv[])
{
  int piels, coors, bud, iron_city, ID, amount;
  FILE *fp = fopen(argv[1], "r");
  fscanf(fp, "%d %d %d %d", &piels, &coors, &bud, &iron_city);

  while(fscanf(fp, "%d %d", &ID, &amount) != EOF)
    switch(ID)
    {
      case PIELS: piels += amount; break;
      case COORS: coors += amount; break;
      case BUD: bud += amount; break;
      case IRON_CITY: iron_city += amount; break;
    } // switch

  printf("Piels:     %5d\n", piels);
  printf("Coors:     %5d\n", coors);
  printf("Bud:       %5d\n", bud);
  printf("Iron City: %5d\n", iron_city);
  fclose(fp);
  return 0;
} // main()

