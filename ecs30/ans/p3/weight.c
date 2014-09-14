// Author: Sean Davis
#include <stdio.h>

int main()
{
  int wt_lb, ht_in;
  double BMI;

  printf("Please enter your weight in whole pounds: ");
  scanf("%d", &wt_lb);
  printf("Please enter your height in whole inches: ");
  scanf("%d", &ht_in);
  BMI = 703.0 * wt_lb / (ht_in * ht_in);
  printf("You have a BMI of %.1lf, and your weight status is ", BMI);

  if(BMI < 18.5)
    printf("underweight.\n");
  else
    if(BMI < 25)
      printf("normal.\n");
    else
      if(BMI < 30)
        printf("overweight.\n");
      else
        printf("obese.\n");
    
  return 0;
} // main()

