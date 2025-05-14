#include <stdio.h>
#include <stdlib.h>
#include "functionals.h"

int* map(const int* array, size_t size, int_unary_fn fn) {
  int* result = malloc(size * sizeof(int));
  if(!result) return NULL;
  for(size_t i = 0; i < size; i++) result[i] = fn(array[i]);

  return result;
}

// int_binary_fn fn é a função passada pelo reduce, ou soma, substrai, multiplica ou etc
int reduce(const int* array, size_t size, int_binary_fn fn, int initial) {
  int accumulator = initial;
  for(size_t i = 0; i < size; i++) accumulator = fn(accumulator, array[i]);
  return accumulator;
}

int* forEach(const int* array, size_t size, size_t totalIndex) {
  size_t limit = (totalIndex < size) ? totalIndex : size;
  int* result = malloc(sizeof(int) * limit);
  if(!result) return NULL;
  for (size_t i = 0; i < limit; i++) result[i] = array[i];
  return result;
}

const int** nestedForEach(const int** array, size_t outerSize, size_t totalIndex) {
  size_t limit = (totalIndex < outerSize) ? totalIndex : outerSize;
  const int** result = malloc(sizeof(int*) * limit);
  if(!result) return NULL;
  for (size_t i = 0; i < limit; i++) result[i] = array[i];
  return result;
}
