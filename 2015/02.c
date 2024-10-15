/*
--- Day 2: I Was Told There Would Be No Math ---
The elves are running low on wrapping paper, and so they need to submit an order for more. They have a list of the dimensions (length l, width w, and height h) of each present, and only want to order exactly as much as they need.

Fortunately, every present is a box (a perfect right rectangular prism), which makes calculating the required wrapping paper for each gift a little easier: find the surface area of the box, which is 2*l*w + 2*w*h + 2*h*l. The elves also need a little extra paper for each present: the area of the smallest side.

For example:

A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52 square feet of wrapping paper plus 6 square feet of slack, for a total of 58 square feet.
A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42 square feet of wrapping paper plus 1 square foot of slack, for a total of 43 square feet.
All numbers in the elves' list are in feet. How many total square feet of wrapping paper should they order?
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum dimension_e {
  LENGTH=0,
  WIDTH,
  HEIGHT,
  SIZE
} dimension_t;
// box surface area: (2*l*w + 2*w*h + 2*h*l)
int min3(int a, int b, int c) {
  int min_ = a;
  if (b < min_)
    min_ = b;
  if (c < min_)
    min_ = c;
  return (min_);
}

int main(int argc, char **argv)
{
  int dim_array[SIZE] = {0};
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
  size_t n = 0, idx = 0, dim = 0;
  char *Line = NULL;
  long area = 0;
  char *tok;
  while (1) {
    dim = 0;
    nread = getline(&Line, &n, fp);
    // TODO: Parse the line
    if (nread <= 0)
      break;
    Line[nread-1] = 0;
    // printf("$%zu `%s`\n", idx, Line);
    
    tok = strtok(Line, "x");
    dim_array[dim++] = atoi(tok);
    while (dim < SIZE) {
      tok = strtok(NULL, "x");
      dim_array[dim++] = atoi(tok);
    }
    area += 
      (2*dim_array[LENGTH]*dim_array[WIDTH] + 2*dim_array[WIDTH]*dim_array[HEIGHT] + 2*dim_array[HEIGHT]*dim_array[LENGTH]);
    // Identify the smallest side and add it up to the area.
    area += 
      min3(dim_array[LENGTH]*dim_array[WIDTH], dim_array[WIDTH]*dim_array[HEIGHT], dim_array[HEIGHT]*dim_array[LENGTH]);
    free(Line);
    Line = NULL;
    idx++;
  }
  printf("the calculated area is: %ld\n", area);
  return (0);
}
