/*Wai Shing Yung 996936848
calc cost of home ownership
@param initial cost, fuel cost, tax rate
10/11/11
*/
#include<stdio.h>

int main()
{
  double initial,fuel;
  float rate,add;
  printf("This program determines the total cost of "
    "owning a home for five years.\n");
  printf("The user will enter initial cost in whole dollars, annual fuel costs"
    " in \n");
  printf("whole dollars, and the annual tax rate as a real number.\n\n");
  printf("Please enter the initial cost, fuel cost, and tax rate: ");
  scanf("%lf %lf %f",&initial,&fuel,&rate);
  fuel *= 5;
  add=initial*rate;
  add *= 5;
  initial += fuel;
  initial += add;
  printf("The total cost is $%.2lf.\n",initial);
  return 0;
}//main
