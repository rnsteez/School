//Wai Shing Yung 996936848
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include"vector.h"
void find_CRN (int s,char ***crn,char ***course, char ***sub)
{
  int i,b;
  char ar[10];
  printf("Please enter a CRN: ");
  fgets(ar,10,stdin);
  for (i=0;i<s;i++)
    if (strcmp(ar,(*crn)[i])==1)
    {
      printf("%s %s\n",(*sub)[i],(*course)[i]);
      b=1;
    }// match crn
    if (b==0);
      printf("CRN %s is not found.\n",ar);
}// find crn

void find_subject(int s,char ***crn,char ***course, char ***sub)
{
  int i,b;
  char ar[10];
  printf("Please enter a subject: ");
  fgets(ar,10,stdin);
  for (i=0;i<s;i++)
    if (strcmp(ar,(*sub)[i])==1)
    {
      printf("%s %s %s\n",(*crn)[i],(*sub)[i],(*course)[i]);
      b=1;
    }//match subject
    if (b==0);
      printf("No courses were found for %s.\n",ar);
}//find subject

void read_courses(int *s,char *file,char ***crn,char ***course, char ***sub)
{
  FILE *fp;
  char *st=NULL,*ar=NULL,*test=NULL;
  int a=0,len,num;

  fp=fopen("file","r");
  while (fgets(ar,80,fp)!=NULL)
  {
    st=strtok(ar,"<>");
    num=strcmp(st,"pre");
    if (num==1)
      while (fgets(NULL,80,fp)!=NULL)
        test=strtok(ar,"\t");
        len=strlen(test);
        if (len==5)
          if (isdigit(test))
            {
            strcpy((*crn)[a],test);
            (*s)+=1;
            test=strtok(NULL,"\t");
            len=strlen(test);
            if (len==1) 
              test=strtok(NULL,"\t");
            strcpy((*sub)[a],test);
            test=strtok(NULL,"\t");
            strcpy((*course)[a],test);
            if (a==(*s-1))
              resize(s,crn,course,sub);
            a+=1;
            }// if line is valid
    num=strcmp(st,"/pre");
    if (num==1)
      break;
  }//scans whole doc
}//read courses

