/* Wai Shing Yung 996936848 
Calculates acceleration of jet
@param takeoff speed, distance
10/5/11
*/
#include <stdio.h>
int
main(void)
{
  printf("Please enter the takeoff speed of the jet in km/hr > ");
  float v0,v1,s,t;
  scanf("%f",&v0);
  printf("Please enter the catapult distance in meters > ");
  scanf("%f",&s);
  v0=v0*1000;
  v0=v0/3600;
  v1=v0*v0;
  float a;
  s=s*2;
  a=v1/s;
  t=v0/a;
  printf("The jet would accelerate at %.2f m/s^2 for %.2f seconds.\n",a,t);
  return (0);
}
