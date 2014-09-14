//Wai Shing Yung
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void free_memory(FILE *fp, FILE *fp2,char *x,char **f,char **s);
void read_names(int i,FILE *fp,char **sur,char **fir,char *mid);
void write_names(int i,FILE *fp,char **sur, char**fir,char *mid);
void sort(int i,char** sur,char** fir,char *mid);

int main(int argc,char *argv[])
{
  FILE *fp;
  FILE *fp2;
  int i,t,m;
  char *middle_init,**first,**surname;
  fp=fopen(argv[1],"r");
  fp2=fopen(argv[2],"w");
  fscanf(fp,"%d",&i);
  middle_init=(char *) malloc (i * sizeof(char));
  first=(char**) malloc (i*sizeof(char *));
  for (t=0;t<i;t++)
    first[t]=(char *) malloc (16*sizeof(char));
  surname=(char**) malloc (i*sizeof(char *));
  for (m=0;m<i;m++)
    surname[m]=(char *) malloc (16*sizeof(char));
  read_names(i,fp,surname,first,middle_init);
  sort(i,surname,first,middle_init);
  write_names(i,fp2,surname,first,middle_init);
  free_memory(fp,fp2,middle_init,first,surname);
  return(0);
}//main

void read_names(int i,FILE *fp,char **sur,char **fir,char *mid)
{
  int c;
  char ar[80], *pt;
  fgets(ar,80,fp);
  strcpy(sur[0],strtok(ar,"., \n"));
  strcpy(fir[0],strtok(NULL,"., \n"));
  pt=strtok(NULL,",. \n");
  mid[0]=*pt;

  for (c=1;c<i;c++)
  {
    fgets(ar,80,fp);
    strcpy(sur[c],strtok(NULL,",. \n"));
    strcpy(fir[c],strtok(NULL,",.\n "));
    pt=strtok(NULL,"., \n");
    mid[c]=*pt;
  }//repeat for whole file
  
  free(pt);
}// read names

void sort(int i,char** sur,char** fir,char *mid)
{
  int c,test;
  char *temps,*tempf,*temp;
  temp=temps=tempf=0;
   
  for (c=0;c<i-1;c++)
  {
    test=strcmp(sur[c],sur[c+1]);
    if (test>0)
      temps=sur[c+1];
      sur[c+1]=sur[c];
      sur[c]=temps;
      tempf=fir[c+1];
      fir[c+1]=fir[c];
      fir[c]=tempf;
      *temp=mid[c+1];
      mid[c+1]=mid[c];
      mid[c]=*temp;
  }//compare all 
  
}//sort

void free_memory(FILE *fp, FILE *fp2,char *x,char **f,char **s)
{
  fclose(fp);
  fclose(fp2);
  free(x);
  free(f);
  free(s);
}//free mem

void write_names(int i,FILE *fp,char **sur, char**fir,char *mid)
{
  int c;
  for (c=0;c<i;c++)
    fprintf(fp,"%-15s%-15s%-15c\n",sur[c],fir[c],mid[c]);
}// write names

