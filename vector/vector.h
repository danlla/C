#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

struct vector;

struct vector* vector_create_memory(size_t n);

struct vector* vector_create_file(const char* path, size_t n);

struct vector* vector_open_file(const char* path);

size_t vector_get_size(struct vector* v);

int vector_get_item(struct vector* v, size_t index);

void vector_set_item(struct vector* v, size_t index, int value);

void vector_free(struct vector* v);

#endif