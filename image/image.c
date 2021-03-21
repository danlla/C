#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct image {
	struct color* data;
	size_t height;
	size_t width;
};

struct image* img_create(const size_t height, const size_t width) {
	struct image* const image = malloc(sizeof(struct image));
	if (image == NULL) {
		return NULL;
	}
	struct color* const data = calloc(height * width, sizeof(struct color));
	if (data == NULL) {
		free(image);
		return NULL;
	}
	image->data = data;
	image->height = height;
	image->width = width;
	return image;
}

struct image* img_load(const char* const path) {
	int width = 0, height = 0, channels = 0;
	unsigned char* const data = stbi_load(path, &width, &height, &channels, 3);
	if (data == NULL) {
		return NULL;
	}
	struct image* const image = img_create(height, width);
	if (image == NULL) {
		stbi_image_free(data);
		return NULL;
	}
	for (size_t i = 0; i < image->height; ++i) {
		for (size_t j = 0; j < image->width; ++j) {
			struct color c = {
				data[i * image->width * 3 + j * 3],
				data[i * image->width * 3 + j * 3 + 1],
				data[i * image->width * 3 + j * 3 + 2]
			};
			img_set_pixel(image, i, j, c);
		}
	}
	stbi_image_free(data);
	return image;
}

bool img_save(const char* path, const struct image* image) {
	unsigned char* const data = malloc(image->height * image->width * 3);
	if (data == NULL) {
		return false;
	}
	for (size_t i = 0; i < image->height; ++i) {
		for (size_t j = 0; j < image->width; ++j) {
			struct color c = img_get_pixel(image, i, j);
			data[i * image->width * 3 + j * 3] = c.r;
			data[i * image->width * 3 + j * 3 + 1] = c.g;
			data[i * image->width * 3 + j * 3 + 2] = c.b;
		}
	}
	const int result = stbi_write_bmp(path, (int)image->width, (int)image->height, 3, data);
	free(data);
	return result;
}

void img_free(struct image* image) {
	free(image->data);
	free(image);
}

size_t img_get_height(const struct image* image) {
	return image->height;
}

size_t img_get_width(const struct image* image) {
	return image->width;
}

struct color img_get_pixel(const struct image* const image, const size_t i, const size_t j) {
	return image->data[i * image->width + j];
}

void img_set_pixel(struct image* const image, const size_t i, const size_t j, const struct color c) {
	image->data[i * image->width + j] = c;
}