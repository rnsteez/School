// Author: Sean Davis
#include <stdio.h>

void display_instructions();

int main()
{
  int initial_cost, fuel;
  double tax_rate, total;

  display_instructions();
  printf("Please enter the initial cost, fuel cost, and tax rate: ");
  scanf("%d%d%lf", &initial_cost, &fuel, &tax_rate);
  total = initial_cost + 5 * (initial_cost * tax_rate + fuel);
  printf("The total cost is $%0.2lf.\n", total);
  return 0;
} // main()

void display_instructions()
{
  printf("This program determines the total cost of owning a home for five ");
  printf("years.\n");
  printf("The user will enter initial cost in whole dollars, annual fuel ");
  printf("costs in \n");
  printf("whole dollars, and the annual tax rate as a real number.\n\n");
} // display_instructions()


