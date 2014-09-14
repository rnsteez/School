// Author: Sean Davis
#ifndef PERMISSIONS_H
	#define PERMISSIONS_H

typedef struct
{
  short octal;
} Permissions;


void print(Permissions *permissions);
void setPermissions(Permissions *permissions, short originalPermissions,
  short umask);


#endif

