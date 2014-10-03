/* Wai Shing Yung 996936848 
calculates reimbursement based on distance traveled 
@param odometer readings
10/5/11
*/
#include <stdio.h>
#define r .35

int
main(void)
{
  float b;
  printf("MILEAGE REIMBURSEMENT CALCULATOR\n");
  printf("Enter beginning odometer reading=> ");
  scanf("%f",&b);
  float e;
  printf("Enter ending odometer reading=> ");
  scanf("%f",&e);
  float t;
  t = e - b;
  float re;
  re = t * r;
  printf("You traveled %.1f miles. At $.35 per mile,\n",t);
  printf("your reimbursement is $%.2f.\n",re);
  return (0);
} // main

