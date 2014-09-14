//Wai Shing Yung 996936848
#include<stdio.h>
#include<math.h>
#define ALLOW 600
#define MONTH 3999
#define OVER_CHARGE 40
#define TAX .0525

int main()
{
  int day, night, end, total;
  float over, cost,avg,tax_amt;
  printf("Please enter the number of weekday minutes, night minutes: ");
  scanf("%d %d",&day, &night);
  printf("Please enter the number of weekend minutes: ");
  scanf("%d",&end);
  if (day>ALLOW)
    over=day-ALLOW;
  else 
    over=0;
  total=day+end+night;
  over=over*OVER_CHARGE;
  cost=MONTH+over;
  avg=cost/total;
  avg/=100;
  printf("\nWeekday minutes: %d, night minutes: %d, weekend minutes: %d\n"
    "Average minute cost: $%.2f\n\n",day,night,end,avg);
  cost/=100;
  printf("Pretax bill: $%5.2f\n",cost);
  tax_amt=cost*TAX;
  printf("Taxes:       $ %5.2f\n",tax_amt);
  cost+=tax_amt;
  printf("Total bill:  $%5.2f\n",cost);
  return(0);
}//main
