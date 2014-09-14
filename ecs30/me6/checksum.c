//Wai Shing Yung 996936848
#include<stdio.h>
#include<string.h>
int main()
{
  int i=1;
  char a,c;
  do
  {
    printf("Line: ");
    a=0;
    c=0;
  
    do
    {
      scanf("%c",&a);
      c+=a;
    } while (a!='\n');
    
    if (c=='8')
    {
      i=0;
      break;
    }
    
    c-=a;
    c%=64;
    c+=' ';
    printf("Checksum: %c\n",c);
    
  } while (i==1); // repeat till '.'

  return 0;
}//main

