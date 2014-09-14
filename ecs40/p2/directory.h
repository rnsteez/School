//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."
// The cake is a lie!
#ifndef DIRECTORY_H
 #define DIRECTORY_H
#define MAX_SUBD 3

#include "permissions.h"

typedef struct Dir
{
	char *name;
	int time;
	struct Dir **subD;
	int numSubD;
	struct Dir *parentD;
	Permissions dPermissions;
} Directory;

void printdir(Directory *currentDirectory); //recursively prints the current directory

#endif
