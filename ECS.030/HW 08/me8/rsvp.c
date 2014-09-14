//Wai Shing Yung
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"course.h"
#include"vector.h"


void display_info(int s,char ***crn,char ***course, char ***sub);
int get_choice(void);

int main(int argc,char *argv[])
{
  int s;
  char **crn,**course,**subject;
  read_courses(&s,argv[1],&crn,&course,&subject);
  display_info(s,&crn,&course,&subject);
  deallocate(s,&crn,&course,&subject);
  return 0;
}//main


void display_info(int s,char ***crn,char ***course, char ***sub)
{
  int i;
  while (i!=0)
  {
  i=get_choice();
  if (i==1)
    find_CRN(s,crn,course,sub);
  if (i==2)
    find_subject(s,crn,course,sub);
  }//loop
}//display info

int get_choice(void)
{
  int choice;
  do
  {
  printf("RSVP Menu\n0. Done.\n1. Find by CRN.\n2. Find by subject.\nYour choice (0 - 2): ");
  scanf("%d",&choice);
  if (choice==0)
    exit(0);
  return (choice);
  }while(choice>2 && choice<0);
}//get choice
