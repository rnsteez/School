// Author: Sean Davis
#include <stdio.h>
#include <math.h>
#define MAX_MINUTES 600
#define FLAT_RATE 3999
#define MINUTE_RATE 40
#define TAX_RATE 0.0525
#define CENTS_PER_DOLLAR 100

int main()
{
  int weekday_minutes, night_minutes, weekend_minutes, pretax_cost, taxes,
    average_minute_cost, total_bill;

  printf("Please enter the number of weekday minutes, night minutes: ");
  scanf("%d%d", &weekday_minutes, &night_minutes);
  printf("Please enter the number of weekend minutes: " );
  scanf("%d", &weekend_minutes);


  if(weekday_minutes <= MAX_MINUTES)
    pretax_cost = FLAT_RATE;
  else // weekday_minutes more than MAX_MINUTES
    pretax_cost = FLAT_RATE + (weekday_minutes - MAX_MINUTES) * MINUTE_RATE;

  average_minute_cost = floor(0.5 + (double) pretax_cost
    / (weekday_minutes + night_minutes + weekend_minutes));

  taxes = floor(0.5 + TAX_RATE * pretax_cost);
  total_bill = pretax_cost + taxes;
  printf("\nWeekday minutes: %d, night minutes: %d, weekend minutes: %d\n",
    weekday_minutes, night_minutes, weekend_minutes);
  printf("Average minute cost: $%.2lf\n\n",
    (double) average_minute_cost / CENTS_PER_DOLLAR);
  printf("Pretax bill: $%6.2lf\n", (double) pretax_cost / CENTS_PER_DOLLAR);
  printf("Taxes:       $%6.2lf\n", (double) taxes / CENTS_PER_DOLLAR);
  printf("Total bill:  $%6.2lf\n", (double) total_bill / CENTS_PER_DOLLAR);
  return 0;
} // main()

