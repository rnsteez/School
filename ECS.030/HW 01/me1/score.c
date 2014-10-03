/* Wai Shing Yung 996936848
Grade percentage calculator
@param current grades
10/5/11
 */
#include <stdio.h>

int
main(void)
{
  char grade;
  float min;
  float cur;
  float final;
  printf("Enter desired grade> ");
  scanf("%c", &grade);
  printf("Enter minimum average required> ");
  scanf("%f", &min);
  printf("Enter current average in course> ");
  scanf("%f", &cur);
  printf("Enter how much the final counts\n");
  printf("as a percentage of the course grade> ");
  scanf("%f", &final);
  float need;
  float curp;
  curp = 100 - final;
  curp = curp / 100;
  float curw;
  curw = curp * cur;
  need = ((min - curw) / final)*100;
  printf("\nYou need a score of %.2f on the final to get a %c.\n",need,grade);
  return (0);
}// main
