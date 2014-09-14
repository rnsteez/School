// Author: Sean Davis

#include <stdio.h>
#include "permissions.h"


void print(Permissions *permissions)
{
  if(permissions->octal & 4)
    printf("r");
  else // 4-bit not set
    printf("-");

  if(permissions->octal & 2)
    printf("w");
  else // 2-bit not set
    printf("-");

  if(permissions->octal & 1)
    printf("x");
  else // 1-bit not set
    printf("-");
} // print()


void setPermissions(Permissions *permissions, short originalPermissions,
  short umask)
{
  permissions->octal = originalPermissions & ~umask;
} // setPermissions()
