// Author: Sean Davis
#include <stdio.h>
#define INITIAL_POPULATION  52.966
#define INITIAL_YEAR 1990
#define GROWTH_RATE 2.184

double population(int years);

int main()
{
  int years;
  FILE *fp;

  printf("Enter a year after %d> ", INITIAL_YEAR);
  scanf("%d", &years);
  fp = fopen("pop.txt", "w");

  fprintf(fp, 
    "Predicted Gotham City population for %d (in thousands): %.3lf\n",
    years, population(years));
  fclose(fp);

  return 0;
} // main()

double population(int years)
{
  return INITIAL_POPULATION + GROWTH_RATE * (years - INITIAL_YEAR);
}  // population()

