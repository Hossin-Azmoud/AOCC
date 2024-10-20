/*
--- Day 7: Some Assembly Required ---
This year, Santa brought little Bobby Tables a set of wires and bitwise logic gates! Unfortunately, little Bobby is a little under the recommended age range, and he needs help assembling the circuit.

Each wire has an identifier (some lowercase letters) and can carry a 16-bit signal (a number from 0 to 65535). A signal is provided to each wire by a gate, another wire, or some specific value. Each wire can only get a signal from one source, but can provide its signal to multiple destinations. A gate provides no signal until all of its inputs have a signal.

The included instructions booklet describes how to connect the parts together: x AND y -> z means to connect wires x and y to an AND gate, and then connect its output to wire z.

For example:

123 -> x means that the signal 123 is provided to wire x.
x AND y -> z means that the bitwise AND of wire x and wire y is provided to wire z.
p LSHIFT 2 -> q means that the value from wire p is left-shifted by 2 and then provided to wire q.
NOT e -> f means that the bitwise complement of the value from wire e is provided to wire f.
Other possible gates include OR (bitwise OR) and RSHIFT (right-shift). If, for some reason, you'd like to emulate the circuit instead, almost all programming languages (for example, C, JavaScript, or Python) provide operators for these gates.

For example, here is a simple circuit:

123 -> x
456 -> y
x AND y -> d
x OR y -> e
x LSHIFT 2 -> f
y RSHIFT 2 -> g
NOT x -> h
NOT y -> i
After it is run, these are the signals on the wires:

d: 72
e: 507
f: 492
g: 114
h: 65412
i: 65079
x: 123
y: 456
In little Bobby's kit's instructions booklet (provided as your puzzle input), what signal is ultimately provided to wire a?
*/
#include <cstdint>
#include <ctype.h>

#include <map>
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

typedef enum operation_kind_e {
  NONE = 0,
  AND,
  OR,
  NOT,
  LSHIFT, // <<
  RSHIFT,  // >>
  WRITE
} operation_kind_t;

typedef struct bitoperation_s {
  operation_kind_t kind = NONE;
  char       *lhs = NULL;
  char       *rhs = NULL;
  char       *dst = NULL;
} bitoperation_t;

bool isdigits(char *s) {
  if (!s)
    return false;
  if (!*s)
    return false;
  for (int i = 0; s[i];i++) {
    if (!isdigit(s[i]))
      return false;
  }
  return true;
}

uint16_t execute_operation(std::map<std::string, uint16_t> &Ram, 
    bitoperation_t instruction, 
    std::map<std::string, bitoperation_t> instructions) { 
  uint16_t result = 0, lhs, rhs;
  if (auto search = Ram.find(instruction.dst); search != Ram.end())
    return search->second; 
  assert(instruction.kind != NONE && "instruction is unknown");
  switch (instruction.kind) {
    case AND: {
      if (isdigits(instruction.lhs))
        lhs = atoi(instruction.lhs);
      else
        lhs = execute_operation(Ram, instructions[instruction.lhs], instructions);
      if (isdigits(instruction.rhs))
        rhs = atoi(instruction.rhs);
      else
        rhs = execute_operation(Ram, instructions[instruction.rhs], instructions);
      result = (lhs & rhs);
    } break;
    case OR: {
      if (isdigits(instruction.lhs))
        lhs = atoi(instruction.lhs);
      else
        lhs = execute_operation(Ram, instructions[instruction.lhs], instructions);
      if (isdigits(instruction.rhs))
        rhs = atoi(instruction.rhs);
      else
        rhs = execute_operation(Ram, instructions[instruction.rhs], instructions);
      result = (lhs | rhs);
    } break;
    case LSHIFT: {
      if (isdigits(instruction.lhs))
        lhs = atoi(instruction.lhs);
      else
        lhs = execute_operation(Ram, instructions[instruction.lhs], instructions);
      if (isdigits(instruction.rhs))
        rhs = atoi(instruction.rhs);
      else
        rhs = execute_operation(Ram, instructions[instruction.rhs], instructions);
      result = (lhs << rhs);
    } break;
    case RSHIFT: {
      if (isdigits(instruction.lhs))
        lhs = atoi(instruction.lhs);
      else
        lhs = execute_operation(Ram, instructions[instruction.lhs], instructions);
      if (isdigits(instruction.rhs))
        rhs = atoi(instruction.rhs);
      else
        rhs = execute_operation(Ram, instructions[instruction.rhs], instructions);
      result = (lhs >> rhs);
    } break;
    case WRITE: {
      if (isdigits(instruction.lhs))
        lhs = atoi(instruction.lhs);
      else
        lhs = execute_operation(Ram, instructions[instruction.lhs], instructions);
      result = lhs;
    } break;
    case NOT: {
      if (isdigits(instruction.lhs))
        lhs = atoi(instruction.lhs);
      else
        lhs = execute_operation(Ram, instructions[instruction.lhs], instructions);
      result = ~lhs;
    } break;
    default: {};
  }
  Ram[instruction.dst] = result;
  return result;
}

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
#define MAX_INST 1024 * 60
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
  // TODO: The way I did it was wrong because I am parsing every line.
  // one by one.. I need to do it diffrently so I can find commands that's associated with wires and compute them
  // 0. x -> a
  // 1. 1 -> x
  // INST0 does not know about x so it needs to look for a command that has the same dest and compute it
  
  bitoperation_t ops[MAX_INST];
  
  bitoperation_t *op = ops;
	size_t ip = 0;
  // HashTable *ram0 = new_hash_table();
  std::map<std::string, uint16_t> ram0;
  std::map<std::string, bitoperation_t> prog;
  char **instruction_toks = NULL;
  ssize_t nread = 1;
  size_t n = 0;
  char *Line = NULL;  
  
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
    // TODO: Parse the line into an instruction thingy
    // TODO: Parse the Line as an instruction
    ops[ip].kind = NONE;

    // TODO: NOT
    if (strcmp(instruction_toks[0], "NOT") == 0) {
      ops[ip].kind = NOT;
      ops[ip].lhs = strdup(instruction_toks[1]);  // NOT *instruction_toks[1] -> instruction_toks[1]
      assert(strcmp(instruction_toks[2], "->") == 0 && "ERROR");
      ops[ip].dst = strdup(instruction_toks[3]);
    } else {
      // TODO: Not a not. lhs OP_KIND rhs -> dst
      ops[ip].lhs = strdup(instruction_toks[0]);
      if (!strcmp(instruction_toks[1], "->")) {
        // TODO: Write op
        ops[ip].kind = WRITE;
        ops[ip].dst = strdup(instruction_toks[2]);
      } else {
        if (!strcmp(instruction_toks[1], "OR")) ops[ip].kind = OR;
        if (!strcmp(instruction_toks[1], "AND")) ops[ip].kind = AND;
        if (!strcmp(instruction_toks[1], "RSHIFT")) ops[ip].kind = RSHIFT;
        if (!strcmp(instruction_toks[1], "LSHIFT")) ops[ip].kind = LSHIFT;
        ops[ip].rhs = strdup(instruction_toks[2]);
        assert(strcmp(instruction_toks[3], "->") == 0 && "ERROR");
        ops[ip].dst = strdup(instruction_toks[4]);
      }
      assert(ops[ip].kind != NONE && "ERROR");
    }
    prog[ops[ip].dst] = op[ip];
    free(Line);
    free_split_result(instruction_toks);
    Line = NULL;
    ip++;
  }
  
  execute_operation(ram0, prog["a"], prog);  
  for (auto m = prog.begin();m != prog.end(); m++) {
    if (m->second.dst) free(m->second.dst);
    if (m->second.lhs) free(m->second.lhs);
    if (m->second.rhs) free(m->second.rhs);
  }
  return (0);
}
