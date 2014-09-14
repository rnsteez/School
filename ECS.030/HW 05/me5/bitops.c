//Wai Shing Yung 996936848
#include<stdio.h>
#include"bitops.h"

short int bitadd(short int x,short int y)
{
  short int store,carry;
  do
  {
    store=(x!=y);
    carry=(x&y);
    carry<<=1;
    x=carry;
    y=store;
  } while(carry>0);
  return (y);
}//bitadd

short int bitsub(short int x,short int y)
{
  return 0;
}// sub

short int bitmul(short int x,short int y)
{
  short int i,o,total=0;
  for (i=1;i<=255;i<<=1)
  { 
    o=(y&i);
    if (o>0)
      total=total+x;
    x<<=1;
  }// iteration
  return (total);
}//bit multiply

short int bitdiv(short int x,short int y)
{
  return 0;
}//div 
