//Wai Shing Yung 996936848
#include<stdio.h>

int main()
{
  int pol_num;
  float per_m, odom, x;
  printf("(1) Carbon monoxide\n(2) Hydrocarbons\n(3) Nitrogen oxides\n(4) Nonme"    "thane hydrocarbons\nEnter pollutant number>> ");
  scanf("%d",&pol_num);
  printf("Enter number of grams emitted per mile>> ");
  scanf("%f",&per_m);
  printf("Enter odometer reading>> ");
  scanf("%f",&odom);
  if (odom<50000)
  {
    if (pol_num==1)
      x=3.4;
    else if (pol_num==2)
      x=0.31;
    else if (pol_num==3)
      x=0.4;
    else 
      x=0.25;
    if (per_m>x)
      printf("Emissions exceed permitted level of %.2f grams/mile.\n",x);
    else      
      printf("Emissions do not exceed permitted level of %.2f grams/mile.\n",x);
  }//if <50000
  else
  {
    if (pol_num==1)
      x=4.2;
    else if (pol_num==2)
      x=0.39;
    else if (pol_num==3)
      x=0.5;
    else 
      x=0.31;
    if (per_m>x)
      printf("Emissions exceed permitted level of %.2f grams/mile.\n",x);
    else
      printf("Emissions do not exceed permitted level of %.2f grams/mile.\n",x);
  }// >50000
  return (0);
}// main
