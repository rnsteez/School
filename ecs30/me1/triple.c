/* Wai Shing Yung 996936848 */
#include <stdio.h>
#include <math.h>

int
main(void)
{
  int m,n;
  printf("Please enter two integers with the first larger than the second > ");
  scanf("%d %d",&m,&n);
  int side1,side2,h;
  side1 = (m * m) - (n * n);
  side2 = 2 * m * n;
  h = (m * m) + (n * n);
  printf("The Pythagorean triple of %d and %d is %d, %d, and %d.\n",m,n,side1,side2,h);
  return (0);
}//main

