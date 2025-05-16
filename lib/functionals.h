#ifndef FUNCTIONALS_H
#define  FUNCTIONALS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef int (*int_unary_fn)(int);
typedef int (*int_binary_fn)(int, int);
typedef void (*int_consumer)(int);
typedef bool (*int_predicate_fn)(int);

typedef enum {NOTHING, JUST} Maybe;
typedef struct {
  Maybe tag;
  int value;
} Int;

typedef struct {
    Maybe tag;
    float value;
} Float;

typedef struct {
    Maybe tag;
    char value;
} Char;

typedef struct {
    Maybe tag;
    void* value; // Usado para tipos genéricos
} Any;

typedef enum {
    TYPE_INT,
    TYPE_SHORT_INT,
    TYPE_UNSIGNED_SHORT_INT,
    TYPE_UNSIGNED_INT,
    TYPE_LONG_INT,
    TYPE_UNSIGNED_LONG_INT,
    TYPE_UNSIGNED_LONG_LONG_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_SIGNED_CHAR,
    TYPE_UNSIGNED_CHAR,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE,
    TYPE_VOID,
} DataType;

typedef struct {
    void* data;
    const char* name;
    DataType type;
} ZippedField;

typedef struct {
    ZippedField* fields;
    size_t fieldNumbers;
    size_t elements;
} Zipped;

int* map(const int* array, size_t size, int_unary_fn fn);
int reduce(const int* array, size_t size, int_binary_fn fn, int initial);
int* forEach(const int* array, size_t size, size_t totalIndex);
const int** nestedForEach(const int** array, size_t outerSize, size_t totalIndex);
int* filter(const int* array, size_t size, int_predicate_fn predicate, size_t* outSize);
int compose(int_unary_fn f, int_unary_fn g, int x);
int find(const int* array, size_t size, int_predicate_fn predicate, bool* found);
int foldl(const int* array, size_t size, int_binary_fn fn, int initial);
int foldr(const int* array, ssize_t size, int_binary_fn fn, int initial);
bool every(const int* array, size_t size, int_predicate_fn predicate);
Zipped zip(ZippedField* fields, size_t fieldNumbers, size_t elements);

#endif
