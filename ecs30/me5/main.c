// Wai Shing Yung 996936848
#include<stdio.h>
#include"bitops.h"

short int get_val(short int x,short int y,char o);
void show_results(short int x,short int y,char o,short int r);

int main ()
{
  int i=1;
  short int val1,val2,valid,ans;
  char op;
  while (i==1)
  {
    printf("\nPlease enter two one-byte "
      "numbers and an operator (0 0+ = done) >>");
    scanf("%hd %hd%c",&val1,&val2,&op);
    if (val1==0 && val2==0)
     // exit(1);
     i=0;
    valid=get_val(val1,val2,op);
    switch (op)
    {
      case('+'):
        ans=bitadd(val1,val2);
        break;

      case('-'):
        ans=bitsub(val1,val2);
        break;
      case('*'):
        ans=bitmul(val1,val2);
        break;
      case('/'):
        ans=bitdiv(val1,val2);
        break;
    } //operator switch
    if (valid==1)
      show_results(val1,val2,op,ans);
  }// while i=1
  return 0;
}// main

short int get_val(short int x,short int y,char o)
{
  short int validn,valido,valid;
  if (o=='+'|| o=='-'|| o=='*'|| o=='/')
    valido=1;
  else
    {
    printf("The operator must be +, -, *, or /.\n");
    valido=0;
    }//invalid operator
  if (x>=0 && x<=255 && y>=0 && y<=255)
    validn=1;
  else
    {
    printf("The numbers must be between 0 and 255, inclusive\n");
    validn=0;
    }//invalid number
  if (validn==1 && valido==1)
    valid=1;
  else//test for valid num and operator
    valid=0;
  return valid;
}// valid test

void show_results(short int x,short int y,char o,short int r)
{
  int i,an;
  printf("%hd %c %hd =",x,o,y);
  for (i=65536; i>=1;i>>=1)
  {
    an=i&r;
    if (an>0)
      printf("1");
    else
      printf("0"); 
  }//iteration
  printf("\n");
}//show result funtion
