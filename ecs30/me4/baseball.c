//Wai Shing Yung
#include<stdio.h>

int main(int argc,char *argv[])
{
  FILE *fp;
  int play;
  double h=0,o=0,at=0;
  double avg;
  char stat;
  fp=fopen(argv[1],"r");
  while (fscanf(fp,"%d",&play) !=EOF)
  {
    printf("\nPlayer %d's record: ",play);
    fscanf(fp," %c",&stat);
    while (stat != '\n')
    {
      printf("%c",stat);
      switch (stat)
      {
        case ('H'):
          h+=1;
          at+=1;
          break;
        case ('O'):
          o+=1;
          at+=1;
          break;
        default:
          break;
      }//switch
      fscanf(fp,"%c",&stat);
    }//while score
    avg=h/at;
    printf("\nPlayer %d's batting average: %.3lf\n",play,avg);
    fscanf(fp,"%d",&play);
    o=0;
    h=0;
    at=0;
  }//while players
  return 0;
}//main
