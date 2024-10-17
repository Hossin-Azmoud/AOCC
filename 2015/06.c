/*
--- Day 6: Probably a Fire Hazard ---
Because your neighbors keep defeating you in the holiday house decorating contest year after year, you've decided to deploy one million lights in a 1000x1000 grid.

Furthermore, because you've been especially nice this year, Santa has mailed you instructions on how to display the ideal lighting configuration.

Lights in your grid are numbered from 0 to 999 in each direction; the lights at each corner are at 0,0, 0,999, 999,999, and 999,0. The instructions include whether to turn on, turn off, or toggle various inclusive ranges given as coordinate pairs. Each coordinate pair represents opposite corners of a rectangle, inclusive; a coordinate pair like 0,0 through 2,2 therefore refers to 9 lights in a 3x3 square. The lights all start turned off.

To defeat your neighbors this year, all you have to do is set up your lights by doing the instructions Santa sent you in order.

For example:

turn on 0,0 through 999,999 would turn on (or leave on) every light.
toggle 0,0 through 999,0 would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
turn off 499,499 through 500,500 would turn off (or leave off) the middle four lights.
After following the instructions, how many lights are lit?
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#define LIGHT_COUNT 1000

typedef enum kind_e {
  TOGGLE = 0,
  TURN_ON,
  TURN_OFF
} Kind;

typedef struct vec2_s {
  int x, y;
} vec2;

typedef struct instruction_s {
  Kind kind;
  vec2 start;
  vec2 end;
} instruction_s;

static bool lights[LIGHT_COUNT][LIGHT_COUNT] = {{0}};

int main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "An input file was not given.\n");
    return (1);
  }
  FILE *fp = fopen(argv[1], "r");
  
  if (!fp) {
    fprintf(stderr, "Could not open `%s` for reading.\n", argv[1]);
    return (1);
  }
  
  ssize_t nread = 1;
  unsigned long nice = 0, bad = 0;
  size_t n = 0;
  char *tok  = NULL;
  char *Line = NULL;
  
  while (1) {
    nread = getline(&Line, &n, fp);
    if (nread <= 0)
      break;
    Line[nread-1] = 0;
    // TODO: Parse the line into an instruction thingy
    tok = strtok(Line, " ");
    while (tok) {
      tok = strtok(NULL, " ");
    }
    free(Line);
    Line = NULL;
  }
  printf("Nice words: %ld Bad words: %ld\n", nice, bad);
  return (0);
}
