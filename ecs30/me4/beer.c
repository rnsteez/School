//Wai Shing Yung 996936848
#include<stdio.h>
#define PIELS 1
#define COORS 2
#define BUD 3
#define IRON_CITY 4

int main(int argc,char *argv[])
{
  FILE *fp;
  int p,c,b,i,inv,trans;
  char test;
  fp=fopen(argv[1],"r");
  fscanf(fp,"%d %d %d %d",&p,&c,&b,&i);
  do
  {
    fscanf(fp,"%d %d",&inv,&trans);
    switch (inv)
    {
      case (PIELS):
      {
        p+=trans;
        trans=0;
        break;
      }//case 1
      case (COORS):
      {
        c+=trans;
        trans=0;
        break;
      }//case 2
      case (BUD):
      {
        b+=trans;
        trans=0;
        break;
      }//case 3
      case (IRON_CITY): 
      {
        i+=trans;
        trans=0;
        break;
      }//case 4
    }//switch
  } while (fscanf(fp,"%c",&test)!=EOF);
  fclose(fp);
  printf("Piels:%10d\n",p);
  printf("Coors:%10d\n",c);
  printf("Bud:%12d\n",b);
  printf("Iron City:%6d\n",i);
  return 0;
}//main


