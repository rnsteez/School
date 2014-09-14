// Author: Sean Davis
#include <stdio.h>

int main()
{
  double x, y;

  printf("Please enter the x and y coordinates: ");
  scanf("%lf%lf", &x, &y);
  printf("(%.1lf, %.1lf) is ", x, y);

  if(x < 0)
  {
    if (y < 0)
      printf("in quadrant III\n");
    else // y is non-negative
      if(y > 0)
        printf("in quadrant II\n");
      else // y is zero
        printf("on the x axis\n");
  } // if x is negative
  else // x is non-negative
    if(x > 0)
    {
      if(y < 0)
        printf("in quadrant IV\n");
      else // y is non-negative
        if(y > 0)
          printf("in quadrant I\n");
        else // y is zero
          printf("on the x axis\n");
    } // if x is positive
    else // x is zero
      if(y == 0)
        printf("the origin\n");
      else // y is non-zero
        printf("on the y axis\n");

  return 0;
} // main()

