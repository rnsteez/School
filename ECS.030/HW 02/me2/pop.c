/*Wai Shing Yung 996936848 
Simulate population growth
@param year
10/11/11
*/
#include<stdio.h>
#define P 52.966
#define YEAR 1990
#define GRW 2.184
double population(int x);
FILE *fp;
int main()
{
  int year;
  double new_pop;
  printf("Enter a year after 1990> ");
  scanf("%d",&year);
  new_pop=population(year);
  fp=fopen("pop.txt","w");
  fprintf(fp, "Predicted Gotham City "
    "population for %d (in thousands): %.3lf\n",year,new_pop);
  fclose(fp);
  return 0;
}// main

double population(int x)
{
  int years_since;
  double final_pop;
  years_since=x-YEAR;
  final_pop=P+GRW*years_since;
  return final_pop;
}//pop
