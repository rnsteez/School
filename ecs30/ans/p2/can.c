// Author: Sean Davis
#include <stdio.h>
#include <math.h>

void display_instructions();
double calc_surface_area(double height, double radius);

int main()
{
  double radius, height, cost_per_area, surface_area, total_cost;
  int quantity;
  FILE *fp;

  fp = fopen("cans.txt", "r");
  display_instructions();
  fscanf(fp, "%lf%lf%lf%d", &radius, &height, &cost_per_area, &quantity);
  surface_area = calc_surface_area(height, radius);
  total_cost = quantity * surface_area * cost_per_area;
  printf("Each can #1 has surface area %8.3lf, and the run will cost $%0.2lf.\n",
    surface_area, total_cost);
  fscanf(fp, "%lf%lf%lf%d", &radius, &height, &cost_per_area, &quantity);
  surface_area = calc_surface_area(height, radius);
  total_cost = quantity * surface_area * cost_per_area;
  printf("Each can #2 has surface area %8.3lf, and the run will cost $%0.2lf.\n",
    surface_area, total_cost);
  fscanf(fp, "%lf%lf%lf%d", &radius, &height, &cost_per_area, &quantity);
  surface_area = calc_surface_area(height, radius);
  total_cost = quantity * surface_area * cost_per_area;
  printf("Each can #3 has surface area %8.3lf, and the run will cost $%0.2lf.\n",
    surface_area, total_cost);
  fclose(fp);
  return 0;
} // main()

void display_instructions()
{
  printf("This program calculates the cost of materials for three open-top ");
  printf("cylindrical\n");
  printf("containers.  It reads the radius, height, cost per square ");
  printf("centimeter, and \n");
  printf("quantity for each container from the file cans.txt.  Each line in ");
  printf("cans.txt has \n");
  printf("the format: radius height cost_per_sq_cm quantity.\n\n");
} // display_instructions()


double calc_surface_area(double height, double radius)
{
  return height * radius * 2 * M_PI + M_PI * radius *radius;
} // calc_surface_area()

