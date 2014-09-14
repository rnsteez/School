// Author: Sean Davis
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  int at_bats, hits, player;
  char record;
  FILE *fp = fopen(argv[1], "r");
  while(fscanf(fp, "%d%c", &player, &record) != EOF)
  {
    at_bats = hits = 0;
    printf("Player %d's record: ", player);
    fscanf(fp, "%c", &record);

    while(record != '\n')
    {
      printf("%c", record);

      if(record == 'H')
      {
        hits++;
        at_bats++;
      } // if a hit

      if(record == 'O')
        at_bats++;

      fscanf(fp, "%c", &record);
    }// while more at bats

    printf("\nPlayer %d's batting average: %.3lf\n\n", player,
      (double) hits/ at_bats);
  } // while more in file

  return 0;
} // main()

