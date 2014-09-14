// Author: Sean Davis
#include <stdio.h>

int get_problem();
void get2_pt(int *x1, int *y1, int *x2, int *y2);
void get_pt_slope(double *slope, int *x, int *y);
void slope_intcpt_from2_pt(int x1, int y1, int x2, int y2,
  double *slope, double *intercept);
double intcpt_from_pt_slope(int x, int y, double slope);
void display2_pt(int x1, int y1, int x2, int y2);
void display_pt_slope(int x, int y, double slope);
void display_slope_intcpt(double slope, double intercept);

int main()
{
  int problem;
  char answer;
  int x1, y1, x2, y2;
  double slope, intercept;

  do
  {
    problem = get_problem();
    if(problem == 1) // two point form
    {
      get2_pt(&x1, &y1, &x2, &y2);
      display2_pt(x1, y1, x2, y2);
      slope_intcpt_from2_pt(x1, y1, x2, y2, &slope, &intercept);
    }  // if two-point form
    else // point-slope form
    {
      get_pt_slope(&slope, &x1, &y1);
      display_pt_slope(x1, y1, slope);
      intercept = intcpt_from_pt_slope(x1, y1, slope);
    }  // else point-slope form

    display_slope_intcpt(slope, intercept);
    printf("\nDo another conversion (Y or N)=> ");
    scanf(" %c", &answer);
    printf("\n");
  }  while(answer == 'Y');
  
  return 0;
} // main()

int get_problem()
{
  int choice;
  
  printf("Select the form that you would like to convert to slope-intercept"
    " form:\n");
  printf("1) Two-point form (you know two points on the line)\n");
  printf("2) Point-slope form (you know the line's slope and one point)\n");
  printf("=> ");
  scanf("%d", &choice);
  printf("\n");
  return choice;
} // get_problem

void get2_pt(int *x1, int *y1, int *x2, int *y2)
{
  printf("Enter the x-y coordinates of the first point separated by a space=> ");
  scanf("%d%d", x1, y1);
  printf("Enter the x-y coordinates of the second point separated by a space=> ");
  scanf("%d%d", x2, y2);
} // get2_pt()

void get_pt_slope(double *slope, int *x, int *y)
{
  printf("Enter the slope=> ");
  scanf("%lf", slope);
  printf("Enter the x-y coordinates of the point separated by a space=> ");
  scanf("%d%d", x, y);
} // get_pt_slope()

void slope_intcpt_from2_pt(int x1, int y1, int x2, int y2,
  double *slope, double *intercept)
{
  *slope = ((double)y2 - y1) / ((double)x2 - x1);
  *intercept = intcpt_from_pt_slope(x1, y1, *slope);
} // slope_intcpt_from2_pt()


double intcpt_from_pt_slope(int x, int y, double slope)
{
  return y - slope * x;
}  // intcpt_from_pt_slope()


void display2_pt(int x1, int y1, int x2, int y2)
{
  printf("\nTwo-point form\n");
  printf("      (%d.00 - %d.00)\n", y2, y1);
  printf("  m = --------------\n");
  printf("      (%d.00 - %d.00)\n", x2, x1);
} // display2_pt()

void display_pt_slope(int x, int y, double slope)
{
  printf("\nPoint-slope form\n");
  printf("  y - %d.00 = %.2lf(x - %d.00)\n", y, slope, x);
}  // display_pt_slope()

void display_slope_intcpt(double slope, double intercept)
{
  printf("\nSlope-intercept form\n");
  printf("  y = %.2lfx ",  slope);
  
  if(intercept < 0)
    printf("- %.2lf\n", -intercept);
  else
    printf("+ %.2lf\n", intercept);
}  // display_slope_intcpt()
