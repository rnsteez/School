/*Wai Shing Yung 996936848
converts runner time to rates
@param time 
10/11/11
*/
#include<stdio.h>
#include<math.h>
#define FT 5280
#define KM 3282
void foo();

int main()
{
  float min,sec;
  float meters,feet;
  foo();
  printf("Minutes for the runner: ");
  scanf("%f",&min);
  printf("Seconds for the runner: ");
  scanf("%f",&sec);
  min=min*60;
  sec=sec+min;
  feet=FT/sec;
  meters=FT*1000;
  meters=meters/KM;
  meters=meters/sec;
  printf("That is %.1f feet per second, ",feet);
  printf("and %.2f meters per second.\n",meters);
  return 0;
} // main

void foo(void)
{
  printf("This program will ask for the minutes and seconds for the time it\n");
  printf("took for a runner to run a mile.  The program will then calculate\n");
  printf("the feet per second and meters per second for that runner.\n\n");
}// foo()
