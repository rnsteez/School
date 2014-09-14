// Author: Sean Davis
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  double smallest, largest, average, sum_squares, deviation, num;
  int i, N;
  FILE *fp = fopen(argv[1], "r");
  fscanf(fp, "%d%lf", &N, &smallest);
  average = largest = smallest;
  sum_squares = largest * largest;

  for(i = 1; i < N; i++)
  {
    fscanf(fp, "%lf", &num);

    if(num < smallest)
      smallest = num;

    if(num > largest)
      largest = num;

    average += num;
    sum_squares += num * num;
  }  // for i

  average /= N;
  deviation = sqrt(sum_squares / N - average * average);
  printf("Smallest: %6.2lf\n", smallest);
  printf("Largest:  %6.2lf\n", largest);
  printf("Average:  %6.2lf\n", average);
  printf("Standard deviation: %6.3lf\n", deviation);
  return 0;
} // main()

