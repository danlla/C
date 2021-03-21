cmake_minimum_required (VERSION 3.11)

project (image C)

add_executable (image_practice image_practice.c "image.h" "image.c" "stb_image.h" "stb_image_write.h")
