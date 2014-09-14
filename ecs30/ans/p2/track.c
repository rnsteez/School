// Author: Sean Davis

#include <stdio.h>
#include <stdlib.h>

#define FEET_PER_MILE 5280
#define FEET_PER_KILOMETER 3282

void print_instructions();

int main()
{
  int minutes;
  double fps, mps, seconds;

  print_instructions();
  printf("Minutes for the runner: ");
  scanf("%d", &minutes);
  printf("Seconds for the runner: ");
  scanf("%lf", &seconds);
  fps = FEET_PER_MILE / (minutes * 60 + seconds);
  mps = fps / (FEET_PER_KILOMETER / 1000.0);
  printf("That is %.1lf feet per second, and %.2lf meters per second.\n", fps, mps);
  return 0;
} // main()

void print_instructions()
{
  printf("This program will ask for the minutes and seconds for the time it\n");
  printf("took for a runner to run a mile.  The program will then calculate\n");
  printf("the feet per second and meters per second for that runner.\n\n");
} // print_instructions()
