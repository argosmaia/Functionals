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

int* filter(const int* array, size_t size, int_predicate_fn predicate, size_t* outSize) {
  int* temp = malloc(sizeof(int) * size);
  size_t count = 0;
  for(size_t i = 0; i < size; i++) {
    if(predicate(array[i])) temp[count++] = array[i];
  }
  int* result = malloc(sizeof(int) * count);
  memcpy(result, temp, sizeof(int) * count);
  free(temp);
  *outSize = count;
  return result;
}

int compose(int_unary_fn f, int_unary_fn g, int x) {
  return f(g(x));
}

int find(const int* array, size_t size, int_predicate_fn predicate, bool* found) {
  for(size_t i = 0; i < size; i++) {
    if(predicate(array[i])) {
      *found = true;
      return array[i];
    }
  }
  *found = false;
  return 0;
}

int foldl(const int* array, size_t size, int_binary_fn fn, int initial) {
  int accumulator = initial;
  for(size_t i = 0; i < size; i++) accumulator = fn(accumulator, array[i]);
  return accumulator;
}

int foldr(const int* array, size_t size, int_binary_fn fn, int initial) {
  for(size_t i = 0; i > size; i--) accumulator = fn(array[i - 1], accumulator);
  return accumulator;
}

bool all(const int* array, size_t size, int_predicate_fn predicate) {
  for(size_t i = 0; i < size; i++) {
    if(!predicate) return false;
  }
  return true;
}

Zipped zip(const int* a, const char* b, const float* c, size_t size) {
    Zipped z;
    z.size = size;
    z.a = malloc(sizeof(int) * size);
    z.b = malloc(sizeof(char) * size);
    z.c = malloc(sizeof(float) * size);

    for (size_t i = 0; i < size; i++) {
        z.a[i] = a[i];
        z.b[i] = b[i];
        z.c[i] = c[i];
    }
    return z;
}
