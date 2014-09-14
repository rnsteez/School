/* Wai Shing Yung 996936848 */
#include <stdio.h>

int
main (void)
{
  int yl,yw,hl,hw;
  printf("Please enter the length and width of the yard > ");
  scanf("%d %d",&yl,&yw);
  printf("Please enter the length and width of the house > ");
  scanf("%d %d",&hl,&hw);
  int ay,ah;
  ay = yl*yw;
  ah = hl*hw;
  int total;
  total = ay-ah;
  int ts,tm,t;
  t= total / 2;
  ts= t % 60;
  tm= t / 60;
  printf("%d square feet will take %d minutes and %d seconds to cut.\n",total,tm,ts);
  return (0);
}//main
