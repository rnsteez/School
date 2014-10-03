/*Wai Shing Yung 996936848
calc material cost for cylinders
@param measurements
10/11/11
*/
#include<stdio.h>
#include<math.h>
FILE *fp;
int main()
{
  float r,h,surf,cost,quant,run;
  int x;
  printf("This program calculates the cost of materials for three open-top"
    " cylindrical\ncontainers.  It reads the radius, height, cost per " 
    "square centimeter, and \nquantity for each container from the file "
    "cans.txt.  Each line in cans.txt has \nthe format: radius height " 
    "cost_per_sq_cm quantity.\n\n");
  fp=fopen("cans.txt","r");
  for (x=1; x<=3; x++)
  {
    fscanf(fp, "%f %f %f %f",&r,&h,&cost,&quant);
    surf=(h*r*M_PI*2)+(M_PI*r*r);
    run= surf * cost * quant;
    printf("Each can #%d has surface area %8.3lf, and the run will cost"
      " $%.2lf.\n",x,surf,run);
  }//for x1 x2 x3
  fclose(fp);
  return 0;
}//main
