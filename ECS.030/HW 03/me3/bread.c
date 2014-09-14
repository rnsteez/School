//Wai Shing Yung 996936848
#include<stdio.h>
void display_instructions(char,char,char);
int calc_baking_time(char,char,char);
  
int main()
{
  int t,secs,mins;
  char type,size,manual;
  printf("Are you making white or sweet bread (w or s)? ");
  scanf(" %c",&type);
  printf("Is this a single or double loaf (s or d)? ");
  scanf(" %c",&size);
  printf("Are you going to bake manually (y or n)? ");
  scanf(" %c",&manual);
  display_instructions(type,size,manual);
  t= calc_baking_time (type,size,manual);
  secs=t%60;
  mins=t/60;
  printf("\nFor a total baking time of %d "
    "minutes and %d seconds.\n",mins,secs);
  return 0;
}// main


void display_instructions(char x,char y,char z)
{
  if (x == 'w'|| x == 'W') //if white
  { 
    printf("Primary kneading: 15 minutes\nPrimary rising: 60 minutes\n"
      "Secondary kneading: 18 minutes\nSecondary rising: 20 minutes\n"
      "Loaf shaping: 2 seconds\n");
    if (z == 'y') //if manual
      printf("You should remove the dough for manual baking.\n");
    else  // not manual
      if (z=='n' && y=='s') // single
        printf("Final rising: 75 minutes\nBaking: 45 minutes 0 seconds\n"
          "Cooling: 30 minutes\n");
      else // double
        printf("Final rising: 75 minutes\nBaking: 67 minutes 30 seconds\n"
          "Cooling: 30 minutes\n");
  }//if white  
  else 
    if (x == 's'|| x == 'S')//if sweet
    {
      printf("Primary kneading: 20 minutes\nPrimary rising: 60 minutes\n" 
        "Secondary kneading: 33 minutes\nSecondary rising: 30 minutes\n"
        "Loaf shaping: 2 seconds\n"); 
      if (z == 'y') // manual
        printf("You should remove the dough for manual baking.\n");
      else //not manual
        if (z=='n' && y=='s')//single
          printf("Final rising: 75 minutes\nBaking: 35 minutes 0 seconds\n"                 "Cooling: 30 minutes\n");
      else  //double
        printf("Final rising: 75 minutes\nBaking: 52 minutes 0 seconds\n"
          "Cooling: 30 minutes\n");
  }//if sweet
  return;
}// display_instructions


int calc_baking_time(char x,char y,char z)
{
  int white=6782;
  int sweet=8582;
  int time_sec;
  if (x == 'w'|| x == 'W')//if white
    if (z=='y')//manual
      time_sec=white;
    else //not manual
      if (z=='n' && y=='s')//single
        time_sec=white+9000;
      else//double
        time_sec=white+10350;
  else  //sweet
    if (z=='y')//manual
      time_sec=sweet;
    else //not manual
      if (z=='n' && y=='s')//single
        time_sec=sweet+8400;
      else //double
        time_sec=sweet+9450;
  return(time_sec);
}// calc_time
