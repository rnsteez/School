//Wai Shing Yung
#include<stdio.h>
#include<stdlib.h>
void find_path(char ar[8][8],int x,int y);


int main(int argc,char *argv[])
{
  FILE *fp=fopen(argv[1],"r");
  int i,j;
  char ar[8][8];
  
  for (i=0;i<9;i++)
  {
    for (j=0;j<8;j++)
      {
      fscanf(fp,"%c",&ar[j][i]);
      printf("%c",ar[j][i]);
      }
  }//reading
  
  find_path(ar,8,8);
  return 0;
}//main

void find_path(char ar[8][8],int x,int y)
{
  if (ar[x-1][y-1]=='x')
    {
    printf("No path was found");
    exit (0);
    }//no exit

  if (ar[x-2][y-1]=='o' && (x-2)>0 && (y-1)>0)
    {
    ar[x-2][y-1]='X';
    x-=1;
    return find_path(ar,x,y);
    }//look left
  
 
}




