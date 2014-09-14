// Author: Sean Davis

#include <stdio.h>
#include "bitops.h"

void get_values(char *op, unsigned short *num1, unsigned short *num2)
{
  int OK;

  do{
    OK = 1;
    
    printf("\nPlease enter two one-byte numbers and an operator ");
    printf("(0 0+ = done) >> ");
    scanf("%hd%hd %c", num1, num2, op);

    if(*op != '+' && *op != '-' && *op != '*' && *op != '/')
    {
      printf("The operator must be +, -, *, or /.\n");
      OK = 0;
    }  // if bad op

    if(*num1 < 0 || *num1 > 255 || *num2 < 0 || *num2 > 255)
    {
      printf("The numbers must be between 0 and 255, inclusive\n");
      OK = 0;
    }  // if a number is out of range.
  } while(OK == 0);
} // get_values()


void show_result(char op, short num1, short num2, short result)
{
  int i;

  printf("%d %c %d = ", num1, op, num2);

  for(i = 0x8000; i > 0; i >>= 1)
    if(result & i)
      printf("1");
    else
      printf("0");

  printf("\n");

} // show_result()


int main()
{
  char op;
  unsigned short num1, num2, result;
  get_values(&op, &num1, &num2);

  while(num1 > 0 || num2 > 0)
  {
    switch(op)
    {
      case '+' : result = add(num1, num2); break;
      case '*' : result = multiply(num1, num2); break;
      case '-' : result = subtract(num1, num2); break;
      case '/' : result = divide(num1, num2); break;
    } // switch

    show_result(op, num1, num2, result);
    get_values(&op, &num1, &num2);
  } // while either number is greater than zero.
  return 0;
}

