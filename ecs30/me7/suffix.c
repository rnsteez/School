//Wai Shing Yung
#include<stdio.h>
#include<string.h>

void foo(char *x,char*y,char *z);

int main()
{
  char ar[80], ar2[80],com[80];
  printf("Word #1: ");
  scanf("%s",ar);
  printf("Word #2: ");
  scanf("%s",ar2);
  foo(ar,ar2,com);
  printf("Common suffix: %s\n",com);
  return(0);
}

void foo(char *x,char*y,char *z)
{
  int a,b,i,d;
  char c;
  
  for (a=0;a<strlen(x)/2;a++)
  {
    c=x[a];
    x[a]=x[strlen(x)-a-1];
    x[strlen(x)-a-1]=c;
  }//reverses the string
  
  for (b=0;b<strlen(y)/2;b++)
  {
    c=y[b];
    y[b]=y[strlen(y)-b-1];
    y[strlen(y)-b-1]=c;
  }//reverses the string
  
  i=1;
  while(strncmp(x,y,i)==0)
  {
    strncpy(z,x,i);
    i++;
  }//test

  for (d=0;d<strlen(z)/2;d++)
  {
    c=z[d];
    z[d]=z[strlen(z)-d-1];
    z[strlen(z)-d-1]=c;
  }//reverses the string back to normal
  
}
