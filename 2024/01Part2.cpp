/*
--- Part Two ---

Your analysis only confirmed what everyone feared: the two lists of location IDs are indeed very different.

Or are they?

The Historians can't agree on which group made the mistakes or how to read most of the Chief's handwriting, but in the commotion you notice an interesting detail: a lot of location IDs appear in both lists! Maybe the other numbers aren't location IDs at all but rather misinterpreted handwriting.

This time, you'll need to figure out exactly how often each number from the left list appears in the right list. Calculate a total similarity score by adding up each number in the left list after multiplying it by the number of times that number appears in the right list.

Here are the same example lists again:

3   4
4   3
2   5
1   3
3   9
3   3

For these example lists, here is the process of finding the similarity score:

    The first number in the left list is 3. It appears in the right list three times, so the similarity score increases by 3 * 3 = 9.
    The second number in the left list is 4. It appears in the right list once, so the similarity score increases by 4 * 1 = 4.
    The third number in the left list is 2. It does not appear in the right list, so the similarity score does not increase (2 * 0 = 0).
    The fourth number, 1, also does not appear in the right list.
    The fifth number, 3, appears in the right list three times; the similarity score increases by 9.
    The last number, 3, appears in the right list three times; the similarity score again increases by 9.

So, for these example lists, the similarity score at the end of this process is 31 (9 + 4 + 0 + 0 + 9 + 9).

Once again consider your left and right lists. What is their similarity score?

*/
#include <cstdint>
#include <ctype.h>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define MAX_TOKENS 12

void free_split_result(char **res)
{
  int idx = 0;
  if (res) {
    while (res[idx]) {
      free(res[idx]);
      idx++;
    }
    free(res);
  }
}

char **split(char *s, const char *delim)
{
  char *sc; // string copy
  char **vec;
  char *tok;
  int vec_idx;

  sc  = strdup(s);
  vec = (char **)malloc(sizeof(char *) * MAX_TOKENS);
  vec_idx = 0;
  tok = strtok(sc, delim);
  while (tok) {
    vec[vec_idx++] = strdup(tok);
    tok = strtok(NULL, delim);
  }
  vec[vec_idx] = NULL;
  free(sc);
  return vec;
}

bool cmp(int x, int y)
{
    return (x < y);
}

#include <set>
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
  
  char **instruction_toks = NULL;
  ssize_t nread = 1;
  size_t n = 0;
  char *Line = NULL;

  std::vector<int> A;
  std::vector<int> B;

  while (1) {
    nread = getline(&Line, &n, fp);
    if (nread <= 0)
      break;
    if (nread-1 == 0) {
      free(Line);
      continue;
    }
    Line[nread-1] = 0;
    instruction_toks = split(Line, " ");
	A.push_back(atoi(instruction_toks[0]));
	B.push_back(atoi(instruction_toks[1]));
	free(Line);
    free_split_result(instruction_toks);
    Line = NULL;
  }
  long distance = 0;
  std::sort(A.begin(), A.end(), cmp);
  std::sort(B.begin(), B.end(), cmp);
  printf("SORTED\n");
  for (int i = 0; i < A.size(); i++) {
	// TODO: Take A[i], find its count in B, then do this d += A[i] * count
	/*distance += abs(A[i] - B[i]);*/
	distance += A[i] * count(B.begin(), B.end(), A[i]);
  }
  printf("Answer: %ld\n", distance);
  return (0);
}
