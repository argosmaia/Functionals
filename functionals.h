#ifndef FUNCTIONALS_H
#define  FUNCTIONALS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef int (*int_unary_fn)(int);
typedef int (*int_binary_fn)(int, int);
typedef void (*int_consumer)(int);

int* map(const int* array, size_t size, int_unary_fn fn);
int reduce(const int* array, size_t size, int_binary_fn fn, int initial);
int* forEach(const int* array, size_t size, size_t totalIndex);
const int** nestedForEach(const int** array, size_t outerSize, size_t totalIndex);

#endif
