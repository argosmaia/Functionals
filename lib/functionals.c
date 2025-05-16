#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionals.h"

int* map(const int* array, size_t size, int_unary_fn fn) {
  int* result = malloc(size * sizeof(int));
  if(!result) return NULL;
  for(size_t i = 0; i < size; i++) result[i] = fn(array[i]);

  return result; //? (map(array, result, 0, size, fn), result);
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
  if (!result) {
    free(temp);
    return NULL;
  }

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

int foldr(const int* array, ssize_t size, int_binary_fn fn, int initial) {
  int accumulator = initial;
  for (ssize_t i = size - 1; i >= 0; i--) accumulator = fn(array[i - 1], accumulator);
  return accumulator;
}

bool all(const int* array, size_t size, int_predicate_fn predicate) {
  for(size_t i = 0; i < size; i++) {
    if (!predicate(array[i])) return false;
  }
  return true;
}

Zipped zip(ZippedField* fields, size_t fieldNumbers, size_t elements) {
    Zipped z;
    z.fieldNumbers = fieldNumbers;
    z.elements = elements;
    z.fields = malloc(sizeof(ZippedField) * fieldNumbers);

    for (size_t i = 0; i < fieldNumbers; i++) {
        z.fields[i].name = fields[i].name;
        z.fields[i].type = fields[i].type;

        size_t sizeTypes = 0;
        switch (fields[i].type) {
          case TYPE_INT:   sizeTypes = sizeof(int); break;
          case TYPE_SHORT_INT: sizeTypes = sizeof(short int); break;
          case TYPE_UNSIGNED_SHORT_INT: sizeTypes = sizeof(unsigned short int); break;
          case TYPE_UNSIGNED_INT: sizeTypes = sizeof(unsigned int); break;
          case TYPE_LONG_INT: sizeTypes = sizeof(long int); break;
          case TYPE_UNSIGNED_LONG_INT: sizeTypes = sizeof(unsigned long int); break;
          case TYPE_UNSIGNED_LONG_LONG_INT: sizeTypes = sizeof(unsigned long long int); break;
          case TYPE_FLOAT: sizeTypes = sizeof(float); break;
          case TYPE_CHAR:  sizeTypes = sizeof(char); break;
          case TYPE_SIGNED_CHAR: sizeTypes = sizeof(signed char); break;
          case TYPE_UNSIGNED_CHAR: sizeTypes = sizeof(unsigned char); break;
          case TYPE_DOUBLE: sizeTypes = sizeof(double); break;
          case TYPE_LONG_DOUBLE: sizeTypes = sizeof(long double); break;
          case TYPE_VOID: sizeTypes = sizeof(void); break;
          default: sizeTypes = 1; break;
        }

        z.fields[i].data = malloc(sizeTypes * elements);
        memcpy(z.fields[i].data, fields[i].data, sizeTypes * elements);
    }

    return z;
}
