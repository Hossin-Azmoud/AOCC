/*
--- Part Two ---
Realizing the error of his ways, Santa has switched to a better model of determining whether a string is naughty or nice. None of the old rules apply, as they are all clearly ridiculous.

Now, a nice string is one with all of the following properties:

It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
For example:

qjhvhtzxzqqjkmpb is nice because is has a pair that appears twice (qj) and a letter that repeats with exactly one letter between them (zxz).
xxyxx is nice because it has a pair that appears twice and a letter that repeats with one between, even though the letters used by each rule overlap.
uurcxstgmygtbstg is naughty because it has a pair (tg) but no repeat with a single letter between them.
ieodomkazucvgmuy is naughty because it has a repeating letter with one between (odo), but no pair that appears twice.
How many strings are nice under these new rules?
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

bool match(char A[3], char B[3]) {
  return A[0] == B[0] && A[1] == B[1];
}

bool is_nice(char *word)
{
  // TODO: It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
  int index = 0;
  int matched_pairs = 0;
  int inbe_pair = 0;
  char pairA[3] = {0};
  char pairB[3] = {0};
  int length = strlen(word);

  while (index < length - 1) {
    pairA[0] = word[index];
    pairA[1] = word[index+1];
    // BUG: We have tp look for that pair all the way to the end.
    for (int i = index + 2; i < length - 1; ++i) {
      pairB[0] = word[i];
      pairB[1] = word[i+1];
      matched_pairs += (int)match(pairA, pairB);
    }
    if (matched_pairs)
      break;
    index++;
  }
  index = 0;
  while (index < length - 2) {
    if (word[index] == word[index+2]) {
      inbe_pair++;
      break;
    }
    index++;
  }

  // TODO: It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
  return (inbe_pair && matched_pairs);
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
  
  ssize_t nread = 1;
  unsigned long nice = 0, bad = 0;
  size_t n = 0;
  char *Line = NULL;
  
  while (1) {
    nread = getline(&Line, &n, fp);
    if (nread <= 0)
      break;
    Line[nread-1] = 0;
    if (is_nice(Line)) {
      nice++; 
    } else {
      bad++;
      // printf("\n");
      // printf("@Word Stats: %s\n", Line);
      // if (has_bad_word)
      //   printf("@Word %s is bad lol\n", Line);
      // if (vowel_count < 3)
      //   printf("@Word requirements: 3 vowels but found %u\n", vowel_count);
      // if (!repeating_chars)
      //   printf("No repeating_chars in %s\n", Line);
      // printf("\n");
    }

    free(Line);
    Line = NULL;
  }
  printf("Nice words: %ld Bad words: %ld\n", nice, bad);
  return (0);
}
