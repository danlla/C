#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>
#include <stdlib.h>

struct color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct image;

struct image* img_create(const size_t height, const size_t width);

struct image* img_load(const char* path);

bool img_save(const char* path, const struct image* image);

void img_free(struct image* image);

size_t img_get_height(const struct image* image);

size_t img_get_width(const struct image* image);

struct color img_get_pixel(const struct image* image, size_t i, size_t j);

void img_set_pixel(struct image* image, size_t i, size_t j, struct color c);

#endif IMAGE_H