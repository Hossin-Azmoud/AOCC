/*
--- Day 3: Perfectly Spherical Houses in a Vacuum ---
Santa is delivering presents to an infinite two-dimensional grid of houses.

He begins by delivering a present to the house at his starting location, and then an elf at the North Pole calls him via radio and tells him where to move next. Moves are always exactly one house to the north (^), south (v), east (>), or west (<). After each move, he delivers another present to the house at his new location.

However, the elf back at the north pole has had a little too much eggnog, and so his directions are a little off, and Santa ends up visiting some houses more than once. How many houses receive at least one present?

For example:

> delivers presents to 2 houses: one at the starting location, and one to the east.
^>v< delivers presents to 4 houses in a square, including twice to the house at his starting/ending location.
^v^v^v^v^v delivers a bunch of presents to some very lucky children at only 2 houses.
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/*
>: 2 
^>v<: 4
^v^v^v^v^v: 2
*/
#define LEFT 1
#define DOWN 2
#define UP 4
#define RIGHT 8

// #define GET_BIT(bits, index) ((bits >> index) & 0x1);
// #define SET_BIT(bits, index) 
#define TESTING
int main(int argc, char **argv)
{
  uint8_t is_visited_mask = UP | DOWN | LEFT | RIGHT;
  if (argc < 2) {
    fprintf(stderr, "An input file was not given.\n");
    return (1);
  }
  #ifdef TESTING
    long unsigned sz = sizeof(is_visited_mask) * 8;
    if (is_visited_mask & LEFT)
      printf("LEFT is set\n");
    
    if (is_visited_mask & DOWN)
      printf("DOWN is set\n");
    
    if (is_visited_mask & UP)
      printf("UP is set\n");
    
    if (is_visited_mask & RIGHT)
      printf("RIGHT is set\n");
    for (long unsigned bit = 0; bit < sz; bit++)
      printf("%c", ((is_visited_mask >> (sz - bit - 1)) & 1) ? '1' : '0');
    printf("\n");
    return (0);
  #else
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
      fprintf(stderr, "Could not open `%s` for reading.\n", argv[1]);
      return (1);
    }
    ssize_t nread = 1;
    size_t n = 0, idx = 0;
    char *Line = NULL;
    // long area = 0;
    // char *tok;
    while (1) {
      nread = getline(&Line, &n, fp);
      // TODO: Parse the line
      if (nread <= 0)
        break;
      Line[nread-1] = 0;
      printf("$%zu `%s`\n", idx, Line);
      
      // tok = strtok(Line, "x");
      free(Line);
      Line = NULL;
      idx++;
    }
    return (0);
  #endif /* ifdef TESTING */
}
