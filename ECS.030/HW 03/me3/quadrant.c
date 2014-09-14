//Wai Shing Yung 996936848
#include<stdio.h>

int main()
{
  float x,y;
  printf("Please enter the x and y coordinates: ");
  scanf("%f %f",&x,&y);
  if (x>0 && y>0)
    printf("(%.1f, %.1f) is in quadrant I\n",x,y);
  else if (x>0 && y<0)
    printf("(%.1f, %.1f) is in quadrant IV\n",x,y);
  else if (x<0 && y>0)
    printf("(%.1f, %.1f) is in quadrant II\n",x,y);
  else if (x<0 && y>0)
    printf("(%.1f, %.1f) is in quadrant III\n",x,y);
  else 
    printf("(%.1f, %.1f) is the origin\n",x,y);
  return(0);
}//main
