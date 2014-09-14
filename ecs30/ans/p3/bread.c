// Author: Sean Davis
#include <stdio.h>

void calc_baking_time(char type, char loaf_size, char manual);
void display_instructions(char type, char loaf_size, char manual);

int main()
{
  char type, loaf_size, manual;

  printf("Are you making white or sweet bread (w or s)? ");
  scanf("%c", &type);
  printf("Is this a single or double loaf (s or d)? ");
  scanf(" %c", &loaf_size);
  printf("Are you going to bake manually (y or n)? ");
  scanf(" %c", &manual);
  display_instructions(type, loaf_size, manual);
  calc_baking_time(type, loaf_size, manual);
  return 0;
} // main()


void calc_baking_time(char type, char loaf_size, char manual)
{
  int minutes, seconds = 2;

  if(type == 'W' || type == 'w')
  {
    minutes = 113;

    if(manual == 'n' || manual == 'N')
    {
      if(loaf_size == 'd' || loaf_size == 'D')
      {
        minutes +=  172;
        seconds += 30; 
      }  // if a double loaf
      else  // a single loaf
        minutes += 150;
    } // if not manual
  }  // if white bread
  else // sweet bread
  {
    minutes = 143;

    if(manual == 'n' || manual == 'N')
    {
      if(loaf_size == 'd' || loaf_size == 'D')
      {
        minutes += 157;
        seconds += 30;
      } // if a double loaf
      else // a single loaf
        minutes += 140;
    } // if not manual
  } // else sweet bread

   printf("\nFor a total baking time of %d minutes and %d seconds.\n", minutes, seconds);
} // calc_baking_time()


void display_instructions(char type, char loaf_size, char manual)
{
  int baking_time, seconds = 0;

  if(type == 'W' || type == 'w')
    printf("Primary kneading: 15 minutes\n");
  else // sweet bread
    printf("Primary kneading: 20 minutes\n");

  printf("Primary rising: 60 minutes\n");

  if(type == 'W' || type == 'w')
  {
    printf("Secondary kneading: 18 minutes\n");
    printf("Secondary rising: 20 minutes\n");
  } // if white bread
  else // sweet bread
  {
    printf("Secondary kneading: 33 minutes\n");
    printf("Secondary rising: 30 minutes\n");
  } // else sweet bread

  printf("Loaf shaping: 2 seconds\n");

  if(manual == 'y' || manual == 'Y')
    printf("You should remove the dough for manual baking.\n");
  else // not manual baking
  {
    printf("Final rising: 75 minutes\n");

    if(type == 'W' || type == 'w')
      baking_time = 45;
    else // sweet bread
      baking_time = 35;

    if(loaf_size == 'D' || loaf_size == 'd')
    {
      baking_time *= 1.5;
      seconds = 30;
    } // if a double loaf

    printf("Baking: %d minutes %d seconds\n", baking_time, seconds);
    printf("Cooling: 30 minutes\n");
  } // else not manual baking.
} // display_instructions
