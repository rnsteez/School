//Wai Shing Yung
#include<stdio.h>
int get_problem(int x);
void get2_pt(int x1,int y1,int x2,int y2,int *b1,int *b2,int *b3,int *b4);
void get_pt_slope(double slope,int x1,int y1,int *b1,int *b2,double *c1);
void slope_intcpt_prom2_pt(int x1,int x2, int y1,int y2,double *m, double *b);
void intcpt_from_pt_slope(int x1,int y1,double slope,double *yin);
void display2_pt(int x1,int x2,int y1,int y2);
void display_slope_intcpt(int x1,int y1,double slope);
void display_pt_slope(int x1,int y1,double slope);
int main(int argc,char *argv[])
{
  FILE *fp ;
  int choice,s,xo1,xo2,yo1,yo2,x1,x2,y1,y2;
  double slope,sl,b,m;
  fp=fopen(argv[1],"r");
  fscanf(fp,"%d",&s);
  choice=get_problem(s);
  if (choice==2)
  {
    fscanf(fp,"%d %d",&x1,&y1);    
    fscanf(fp,"%d %d",&x2,&y2);
    get2_pt(x1, x2, y1, y2, &xo1, &yo1, &xo2, &yo2);
    slope_intcpt_prom2_pt(xo1,xo2,yo1,yo2,&m,&b);
    display2_pt(xo1,xo2,yo1,yo2);
    display_slope_intcpt(xo1,yo1,m);
  }//if 2pt form
  else
  {
    fscanf(fp,"%lf",&sl);
    fscanf(fp,"%d %d",&x1,&y1);
    get_pt_slope(sl,x1,y1,&xo1,&yo1,&slope);
    intcpt_from_pt_slope(xo1,yo1,slope,&b);
    display_pt_slope(xo1,yo1,slope);
    display_slope_intcpt(xo1,yo1,slope);
  }//else pt slope form
  return 0;
}//main

int get_problem(int x)
{
  printf("Select the form that you would like to convert to slope-inter"
    "cept form:\n1) Two-point form (you know two points on the line)\n2)"
    " Point-slope form (you know the line's slope and one point)\n=> ");
  return (x);
}// get_problem function

void get2_pt(int x1,int y1,int x2,int y2,int *b1,int *b2,int *b3,int *b4)
{
  printf("Enter the x-y coordinates of the first point seperated by a "
    "space=> ");
  printf("Enter the x-y coordinates of the second point seperated by "
    "a space=> ");
  *b1=x1; 
  *b2=y1;
  *b3=x2;
  *b4=y2;
}//get2pt function

void get_pt_slope(double slope,int x1,int y1,int *b1,int *b2,double *c1)
{
  printf("Enter the slope=> ");
  printf("Enter the x-y coordinates of the point seperated by a space=> ");
  *b1=x1;
  *b2=y1;
  *c1=slope;
} // get pt slope function

void slope_intcpt_prom2_pt(int x1,int x2, int y1,int y2,double *m, double *b)
{
  double temp,tempx,tempy,sl;
  tempy=y2-y1;
  tempx=x2-x1;
  sl=tempy/tempx;
  temp=y1-sl*x1;
  *b=temp;
  *m=sl;
}//slope int prom 2 pts function

void intcpt_from_pt_slope(int x1,int y1,double slope,double *yin)
{
  double temp;
  temp=y1-slope*x1;
  *yin=temp;
}// int from pt slope function

void display2_pt(int x1,int x2,int y1,int y2)
{
  printf("      (%.1d - %.2d\n",y2,y1);
  printf("  m = --------------\n"); 
  printf("      (%.1d - %.2d\n",x2,x1);
}//diplay 2 pt function

void display_pt_slope(int x1,int y1,double slope)
{ 
  printf("Point-slope form\n");
  printf("  Y - %.2d = %.2lf(x - %.2d)",y1,slope,x1);
}//display pt slope form function

void display_slope_intcpt(int x1,int y1,double slope)
{
  double temp;
  temp=y1-slope*x1;
  printf("Slope-intercept form\n");
  printf("  y = %.2lfx - %.2lf",slope,temp);
}//display slope intercept function
