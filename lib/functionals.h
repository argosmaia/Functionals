#ifndef FUNCTIONALS_H
#define  FUNCTIONALS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef int (*int_unary_fn)(int);
typedef int (*int_binary_fn)(int, int);
typedef void (*int_consumer)(int);
typedef bool (*int_predicate_fn)(int);
typedef struct {
    int* a;
    char* b;
    float* c;
    size_t size;
} Zipped;

int* map(const int* array, size_t size, int_unary_fn fn);
int reduce(const int* array, size_t size, int_binary_fn fn, int initial);
int* forEach(const int* array, size_t size, size_t totalIndex);
const int** nestedForEach(const int** array, size_t outerSize, size_t totalIndex);
int* filter(const int* array, size_t size, int_predicate_fn predicate, size_t* outSize);
int compose(int_unary_fn f, int_unary_fn g, int x);
int find(const int* array, size_t size, int_predicate_fn predicate, bool* found);
int foldl(const int* array, size_t size, int_binary_fn fn, int initial);
int foldr(const int* array, size_t size, int_binary_fn fn, int initial);
bool every(const int* array, size_t size, int_predicate_fn predicate);
Zipped zip(const int* a, const char* b, const float* c, size_t size);

#endif
