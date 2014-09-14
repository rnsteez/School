//Wai Shing Yung 996936848
#include<stdio.h>
#include<math.h>

int main()
{
  float wt_lb,ht_in;
  float bmi;
  printf("Please enter your weight in whole pounds: ");
  scanf("%f",&wt_lb);
  printf("Please enter your height in whole inches: ");
  scanf("%f",&ht_in);
  ht_in=ht_in*ht_in;
  bmi=(703*wt_lb)/ht_in;
  if (bmi<18.5)
    printf("You have a BMI of %.1f, and your weight status is underweight.\n",bmi);
  else if (bmi>18.5 && bmi<24.9)
    printf("You have a BMI of %.1f, and your weight status is normal.\n",bmi);
  else if (bmi>24.9 && bmi<29.9)
    printf("You have a BMI of %.1f, and your weight status is overweight",bmi);
  else 
    printf("You have a BMI of %.1f, and your weight status is obese.\n",bmi); 
  return(0);
}//main
