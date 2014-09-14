// Author: Sean Davis
#include <stdio.h>

int main()
{
  int pollutant, odometer;
  double grams, allowed;

  printf("(1) Carbon monoxide\n");
  printf("(2) Hydrocarbons\n");
  printf("(3) Nitrogen oxides\n");
  printf("(4) Nonmethane hydrocarbons\n");
  printf("Enter pollutant number>> ");
  scanf("%d", &pollutant);
  printf("Enter number of grams emitted per mile>> ");
  scanf("%lf", &grams);
  printf("Enter odometer reading>> ");
  scanf("%d", &odometer);

  if(odometer <= 50000)
    switch(pollutant)
    {
      case 1 : allowed = 3.4; break;
      case 2 : allowed = 0.31; break;
      case 3 : allowed = 0.4; break;
      case 4 : allowed = 0.25; break;
    } // switch
  else // odometer > 50000 miles
    switch(pollutant)
    {
      case 1 : allowed = 4.2; break;
      case 2 : allowed = 0.39; break;
      case 3 : allowed = 0.5; break;
      case 4 : allowed = 0.31; break;
    } // switch

  if(grams <= allowed)
    printf("Emissions do not exceed permitted level of %.2lf grams/mile.\n",
      allowed);
  else
    printf("Emissions exceed permitted level of %.2lf grams/mile.\n",
      allowed);

  return 0;
} // main()

