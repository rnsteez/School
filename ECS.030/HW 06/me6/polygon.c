//Wai Shing Yung 996936848 
#include<stdio.h>
#include<stdlib.h>
#define MAX 20


int get_corners(FILE *fp,double x[],double y[],int m);
void output_corners(FILE *fp,double x[],double y[],int n);
int  polygon_area(double x[],double y[],int m,int n);

int main(int argc,char* argv[])
{
  int n;
  FILE *fp=fopen(argv[1],"r");
  FILE *fp2=fopen(argv[2],"w");
  double a[20],b[20],ans;
  n=get_corners(fp,a,b,MAX);
  output_corners(fp2,a,b,n);
  ans=polygon_area(a,b,MAX,n);
  printf("The area is %.1lf.\n",ans);
  return 0;
}// main

int get_corners(FILE *fp,double x[],double y[],int m)
{
  int i=0,c=1;
  while (c!=EOF)
  {
    c=fscanf(fp,"%lf %lf\n",&x[i],&y[i]);
    i++;
  }

  return (i);
}//get corners

void output_corners(FILE *fp,double x[],double y[],int n)
{
  int i;
  for (i=0;i<n-1;i++)
    fprintf(fp,"%.1lf %.1lf\n",x[i],y[i]);

}// output

int  polygon_area(double x[],double y[],int m,int n)
{
  int i;
  double a=0,b,c;
  for (i=0;i<(n);i++)
  {
    c=y[i+1]-y[i];
    b=x[i+1]+x[i];
    a+=b*c;
  }//loop
  a=abs(a);
  a/=2;
return (a);
}//area
