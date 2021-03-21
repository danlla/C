#include <stdio.h>
#include "image.h"
#include "math.h"

struct point
{
	int x;
	int y;
};

void draw_line(struct image* image, const struct color color, const struct point p1, const struct point p2)
{
	const int deltax = abs(p2.x - p1.x);
	const int deltay = abs(p2.y - p1.y);
	const int signx = p1.x < p2.x ? 1 : -1;
	const int signy = p1.y < p2.y ? 1 : -1;
	int error = deltax - deltay;
	img_set_pixel(image, p2.y, p2.x, color);
	int x = p1.x;
	int y = p1.y;
	while (x != p2.x || y != p2.y)
	{
		img_set_pixel(image, y, x, color);
		int error2 = error * 2;
		if (error2 > -deltay)
		{
			error -= deltay;
			x += signx;
		}
		if (error2 < deltax)
		{
			error += deltax;
			y += signy;
		}
	}
}

void draw_circle(struct image* image, const struct color color, const struct point center, const int radius)
{
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= 0)
	{
		img_set_pixel(image,center.y + y, center.x + x,color);
		img_set_pixel(image, center.y - y, center.x + x, color);
		img_set_pixel(image, center.y + y, center.x - x, color);
		img_set_pixel(image, center.y - y, center.x - x, color);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0)
		{
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0)
		{
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}

int main(void)
{
	const char* path = "output.bmp";

	// Чтение
	struct image* image = img_create(50, 50);
	printf("%zu %zu\n", img_get_height(image), img_get_width(image));

	// Изменение
	/*struct color orange = { 255, 127, 39 };
	img_set_pixel(image, 4, 49, orange);*/
	struct color white = { 255,255,255 };
	struct color red = { 255,0,0 };
	struct color pink = { 255,105,180 };
	struct point p1 = { 24,24 };
	struct point p2 = { 49,49 };
	struct point p3 = { 0,0 };
	draw_circle(image, white, p1, 20);
	draw_line(image, red, p3, p2);
	p3.x = 49;
	p3.y = 49;
	p2.x = 49;
	p2.y = 0;
	draw_line(image, red, p3, p2);
	p3.x = 0;
	p3.y = 49;
	draw_line(image, red, p3, p2);
	p2.x = 0;
	draw_line(image, red, p3, p2);
	p3.x = 12;
	p3.y = 24;
	draw_circle(image, white, p3, 6);
	draw_circle(image, pink, p3, 2);
	draw_circle(image, pink, p3, 1);
	p3.x += 24;
	draw_circle(image, white, p3, 6);
	draw_circle(image, white, p3, 1);
	// Сохранение
	img_save(path, image);

	// Освобождение
	img_free(image);
}