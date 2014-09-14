//Wai Shing Yung
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
  char ar[80],*pt,*store[80];
  int i,l,t=1,m;
  for (l=0;l<80;l++)
    store[l]=(char *)malloc(80*sizeof(char));
  printf("Input: ");
  fgets(ar,80,stdin);
  pt=strtok(ar," ");
  strcpy(store[0],pt);
  for (i=1;i<80;i++)
  {
    pt=strtok(NULL," \n");
    if (pt==NULL)
      break;
    strcpy(store[i],pt);
    t+=1;
  }
  printf("Reversed:");
  for (m=t;m>=0;m--)
    printf("%s ",store[m]);
  printf("\n");
  return 0;
}
