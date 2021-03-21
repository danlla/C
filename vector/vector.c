#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

typedef size_t vector_get_size_f(void* context);
typedef int vector_get_item_f(void* context, size_t index);
typedef void vector_set_item_f(void* context, size_t index, int value);
typedef void vector_free_f(void* context);



// =============
// MEMORY VECTOR
// =============

static void* vector_memory_create(const size_t n) {
	void* const context = calloc(sizeof(size_t) + n * sizeof(int), 1);
	if (context == NULL)
		return NULL;
	*((size_t*)context) = n;
	return context;
}

static size_t vector_memory_get_size(void* const context) {
	return *((size_t*)context);
}

static int vector_memory_get_item(void* const context, const size_t index) {
	const unsigned char* data = (const unsigned char*)context;
	data += sizeof(size_t);
	return ((const int*)data)[index];
}

static void vector_memory_set_item(void* const context, const size_t index, const int value) {
	unsigned char* data = (unsigned char*)context;
	data += sizeof(size_t);
	((int*)data)[index] = value;
}

static void vector_memory_free(void* context) {
	free(context);
}



// ===========
// FILE VECTOR
// ===========

static void* vector_file_create(const char* path, const size_t n) {
	void* const context = fopen(path, "w+");
	if (context == NULL)
		return NULL;
	//fprintf(context, "%zu", n);
	for(size_t i = 0;i<n;++i)
		fprintf(context, "%d ", 0);
	return context;
}

static size_t vector_file_get_size(void* const context) {
	/*rewind(context);
	size_t size = 0;
	fscanf(context, "%zu", &size);
	return size;*/
	rewind(context);
	size_t size = 0;
	int tmp = 0;
	while (fscanf(context, "%d ", &tmp) != EOF)
		++size;
	return size;
}

static int vector_file_get_item(void* const context, const size_t index) {
	/*fseek(context, sizeof(size_t)+2*index, SEEK_SET);
	int item = 0;
	fscanf(context, "%d ", &item);
	return item;*/
	fseek(context, 2*index, SEEK_SET);
	int item = 0;
	fscanf(context, "%d ", &item);
	return item;
}

static void vector_file_set_item(void* const context, const size_t index, const int value) {
	//fseek(context, sizeof(size_t) + 2*index, SEEK_SET);
	fseek(context, 2*index, SEEK_SET);
	fprintf(context, "%d ", value);
}

static void vector_file_free(void* context) {
	fclose(context);
}



// ======
// VECTOR
// ======

struct vector {
	void* context;
	vector_get_size_f* get_size_f;
	vector_get_item_f* get_item_f;
	vector_set_item_f* set_item_f;
	vector_free_f* free_f;
};

struct vector* vector_create_memory(size_t n) {
	struct vector* v = calloc(1, sizeof(struct vector));
	if (v == NULL)
		return NULL;
	v->context = vector_memory_create(n);
	if (v->context == NULL)
	{
		free(v);
		return NULL;
	}
	v->get_size_f = vector_memory_get_size;
	v->get_item_f = vector_memory_get_item;
	v->set_item_f = vector_memory_set_item;
	v->free_f = vector_memory_free;
	return v;
}

struct vector* vector_create_file(const char* path, size_t n) {
	struct vector* v = calloc(1, sizeof(struct vector));
	if (v == NULL)
		return NULL;
	v->context = vector_file_create(path, n);
	if (v->context == NULL)
	{
		free(v);
		return NULL;
	}
	v->get_size_f = vector_file_get_size;
	v->get_item_f = vector_file_get_item;
	v->set_item_f = vector_file_set_item;
	v->free_f = vector_file_free;
	return v;
}

struct vector* vector_open_file(const char* path) {
	struct vector* v = calloc(1, sizeof(struct vector));
	if (v == NULL)
		return NULL;
	v->context = fopen(path, "r+");
	if (v->context == NULL)
	{
		free(v);
		return NULL;
	}
	v->get_size_f = vector_file_get_size;
	v->get_item_f = vector_file_get_item;
	v->set_item_f = vector_file_set_item;
	v->free_f = vector_file_free;
	return v;
}

size_t vector_get_size(struct vector* v) {
	return v->get_size_f(v->context);
}

int vector_get_item(struct vector* v, size_t index) {
	return v->get_item_f(v->context, index);
}

void vector_set_item(struct vector* v, size_t index, int value) {
	v->set_item_f(v->context, index, value);
}

void vector_free(struct vector* v) {
	v->free_f(v->context);
	v->context = NULL;
	v->get_size_f = NULL;
	v->get_item_f = NULL;
	v->set_item_f = NULL;
	v->free_f = NULL;
	free(v);
}