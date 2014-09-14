//Wai Shing Yung 996936848
#include<stdio.h>
#include<math.h>

int main(int arg,char *argv[])
{
  FILE *fp;
  int num,i;
  float x,small,large,avg,std,sum_sq,avg2;
  fp=fopen(argv[1],"r");
  fscanf(fp,"%d",&num);
  fscanf(fp,"%f",&x);
  avg=x;
  sum_sq=x*x;
  small=x;
  large=x;
  for (i=1;i<num;i++)
  {
    fscanf(fp,"%f",&x);
    avg+=x;
    if (x>large)
      large=x;
    if (x<small)
      small=x;
    sum_sq=sum_sq+(x*x);
  } // for num  
  avg=avg/num;
  std=(sum_sq/num);
  avg2=avg*avg;
  std=std-avg2;
  std=sqrt(std);
  printf("Smallest:%7.2f\n",small);
  printf("Largest:%8.2f\n",large);
  printf("Average:%8.2f\n",avg);
  printf("Standard deviation:%7.3f\n",std);
  return 0;
}//main

