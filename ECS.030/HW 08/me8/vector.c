//Wai Shing Yung 996936848
#include<stdlib.h>

void deallocate(int s,char ***crn,char ***course, char ***sub)
{
  int i;
  for (i=0;i<s;i++)
    free(course[i]);
  free (crn);
  for (i=0;i<s;i++)
    free(course[i]);
  free (course);
  for (i=0;i<s;i++)
    free(sub[i]);
  free (sub);
}//deallocate

void initialize(char ***crn,char ***course, char ***sub)
{
  int i;
  (*crn)=(char **)malloc(sizeof(char)*100);
  for (i=0;i<100;i++)
    (*crn)[i]=(char *)malloc(sizeof(char)*6);
  (*course)=(char **)malloc(sizeof(char *)*100);
  for (i=0;i<100;i++)
    (*course)[i]=(char *)malloc(sizeof(char)*6);
  (*sub)=(char **)malloc(sizeof(char *)*100);
  for (i=0;i<100;i++)
    (*sub)[i]=(char *)malloc(sizeof(char)*4);
}//initialize

void resize(int *s,char ***crn,char ***course,char ***sub)
{
  int i;
  char **temp = (char **)malloc(*s * 2 *sizeof(char*)), **temp2 = (char **)malloc(*s * 2 *sizeof    (char*)), **temp3 = (char   **)malloc(*s * 2 *sizeof(char*));
  for (i=0;i<*s;i++)
    temp[i]=(*crn)[i];
  for (;i<(*s)*2;)
    temp[i]=(char *)malloc(6*sizeof(char));
  free(*crn);
  *crn=temp;
  for (i=0;i<*s;i++)
    temp2[i]=(*course)[i];
  for (;i<(*s)*2;)
    temp2[i]=(char *)malloc(6*sizeof(char));
  free(*course);
  *course=temp2;
  for (i=0;i<*s;i++)
    temp3[i]=(*sub)[i];
  for (;i<(*s)*2;)
    temp3[i]=(char *)malloc(4*sizeof(char));
  free(*sub);
  *sub=temp3;
  *s *=2;
}//resize

