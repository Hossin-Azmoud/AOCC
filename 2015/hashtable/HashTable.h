#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CAP 64
// f, No generics in C so I probably need to make the same struct for every type I need hh...
typedef struct Cell {
	char *key;
	uint16_t value;
	bool taken;
} Cell;

typedef struct HashTable {
	Cell *Cells;
	size_t size;
	size_t cap;
} HashTable;

void display_cells(HashTable *table);
void distroy_hash_table(HashTable *self);
void expand_table(HashTable *self) ;
void fill_cells(Cell *cells, size_t size) ;
bool get(HashTable *self, char *key, Cell *bucket);
bool insert(HashTable *self, char *key, uint16_t value);
HashTable *new_hash_table(void);
bool contains(HashTable *self, char *key);
