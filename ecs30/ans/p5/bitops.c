// Author Sean Davis

#include "bitops.h"

unsigned short add(unsigned short num1, unsigned short num2)
{
  unsigned short i, result = 0, carry = 0;

  for(i = 1; i <= 0x100; i = i << 1)
    if(carry)
    {
      if((num1 & i) && (num2 & i))
        result = result | i;
      else // both bits not set
        if(!(num1 & i) && !(num2 & i))
        {
          result = result | i;
          carry = 0;
        } // if both bits are zero.
    } // if carry set
    else  // carry not  set
      if(num1 & i && num2 & i)
        carry = 1;
      else  // not both num1 and num2
        if(num1 & i || num2 & i)
          result = result | i;
  return result;
} // add()


unsigned short subtract(unsigned short num1, unsigned short num2)
{
  unsigned short i, result = 0, borrow = 0;

  for(i = 1; i <= 0x100; i <<= 1)
    if(borrow)
    {
      if((num1 & i) && ((num2 & i) == 0))
        borrow = 0;
      else // not (num1 bit == 1 and num2 bit == 0)
        if((num1 & i) && (num2 & i))
          result = result | i;
        else // num1 bit == 0
          if((num2 & i) == 0)
            result = result | i;
    } // if borrow
    else // not borrow
    {
      if((num1 & i) && ((num2 & i) == 0))
        result = result | i;
      else // not (num1 bit == 1 and num2 bit == 0)
        if(((num1 & i) == 0) && (num2 & i))
        {
          result = result | i;
          borrow = 1;
        }  // if
    } // else no borrow

  return result;
} // subtract()


unsigned short multiply(unsigned short num1, unsigned short num2)
{
  unsigned short i, result = 0;


  for(i = 1; i <  0x100; i <<= 1)
  {
    if(num2 & 1)
      result = result + num1;
    num1 = num1 << 1;
    num2 = num2 >> 1;
  }  // for each bit

  return result;
} // multiply()


unsigned short divide(unsigned short num1, unsigned short num2)
{
  unsigned short i, result = 0;

  num2 = num2 << 8;

  for(i = 0x100; i > 0; i = i >> 1)
  {
    if(num1 >= num2)
    {
      result = result | i;
      num1 = num1 - num2;
    } // if

    num2 = num2 >> 1;
  } // for each bit

  return result;
} // divide()
