#include <stdio.h>
#include "vector.h"

int main(void) {
	//struct vector* const v = vector_create_memory(5);
	struct vector* const v = vector_create_file("D:\\test4.txt",1000000);

	const size_t n = vector_get_size(v);

	for (size_t i = 0; i < n; ++i) {
		vector_set_item(v, i, (int)(2 * i + 1)%10);
	}

	for (size_t i = 0; i < n; ++i) {
		printf("%d ", vector_get_item(v, i));
	}
	vector_free(v);
}