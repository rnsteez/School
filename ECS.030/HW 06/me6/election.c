// Wai Shing Yung 996936848
#include<stdio.h>

//void sort(int *ar);
FILE *read_file(char *fp,int *a[][5]);
//void show_table();
//void declare_winner();

int main (int argc,char *argv[])
{
  FILE *fid;
  int ar[5][5];
  fid=read_file(argv[1],ar);
  
  return 0;
}

FILE *read_file(char *fp,int *a)
{
  int i,l;
  FILE *fid;
  fid=fopen(fp,"r");
  for (i=0;i<5;i++)
    for (l=0;l<5;l++)
      fgets(a[i][l],5,fid);
  return (fid);
}
