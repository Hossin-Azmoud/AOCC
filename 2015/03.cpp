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
#include <cstdint>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
using namespace std;
#define ROBOT 0
#define SANTA 1
typedef uint8_t Turn;

void handle_preset(set<vector<int>>& Map, vector<int>& Position, char instruction) {
  switch (instruction) {
    case '>': {
      Position[0]++;
    } break;
    case '<': {
      Position[0]--;
    } break;
    case '^': {
      Position[1]++;
    } break;
    case 'v': {
      Position[1]--;
    } break;
    default:  fprintf(stderr, "Illegal op: %c\n", instruction); exit(1);
  }
  Map.insert(Position);
}

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
  // SANTA WILL START.
  Turn t = SANTA;
  ssize_t nread = 1;
  vector<int> curr_santa_pos = {0,0};
  vector<int> curr_bot_pos = {0,0};
  size_t n = 0, idx = 0;
  char *Line = NULL;

  std::set<vector<int>> santa_map;
  std::set<vector<int>> bot_map;

  santa_map.insert(curr_santa_pos);
  bot_map.insert(curr_bot_pos);


  while (1) {
    nread = getline(&Line, &n, fp);
    if (nread <= 0)
      break;
    Line[nread-1] = 0;
    // printf("$%zu `%s`\n", idx, Line);
    for (;Line[idx];idx++) {
      if (t == SANTA) {
        handle_preset(santa_map, curr_santa_pos, Line[idx]); 
        t = ROBOT;
      } else {
        handle_preset(bot_map, curr_bot_pos, Line[idx]); 
        t = SANTA;
      }
    }
    // tok = strtok(Line, "x");
    free(Line);
    Line = NULL;
  }
  set<vector<int>> FinalM;
  for (auto& vec : santa_map)
    FinalM.insert(vec);
  for (auto& vec : bot_map)
    FinalM.insert(vec);
  printf("visited_houses_: %zu\n", FinalM.size());
  return (0);
}
