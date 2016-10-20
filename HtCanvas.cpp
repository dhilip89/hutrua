#include <cassert>
#include <cstdlib>
#include <cstring>
#include "HtCanvas.h"

HtCanvas::HtCanvas(int width, int height, HtCanvasType type)
{
	assert(width > 0 && height > 0);

	HtCanvas::width = width;
	HtCanvas::height = height;
	HtCanvas::type = type;

	switch (type) {
	case RGBA8888:
		bytes_per_pixel = 4;
		break;
	default:
		exit(1);
	}

	int size = width * height * bytes_per_pixel * sizeof(unsigned char);

	src = (unsigned char*)malloc(size);
	if (!src) {
		exit(1);
	}
	memset(src, 255, size);
}

void HtCanvas::drawRect(HtRect rect, HtColor color) {
	if (rect.size.w <= 0) return;
	if (rect.size.h <= 0) return;
	if (rect.top_left.x < 0) rect.top_left.x = 0;
	if (rect.top_left.y < 0) rect.top_left.y = 0;
	if (int(rect.top_left.x) + int(rect.size.w) > width) rect.size.w = width - int(rect.top_left.x);
	if (int(rect.top_left.y) + int(rect.size.h) > height) rect.size.h = height - int(rect.top_left.y);

	assert(sizeof(HtColor) == 4);
	unsigned char* row_pointer = src + int(rect.top_left.y) * bytes_per_pixel * width + int(rect.top_left.x) * bytes_per_pixel;
	for (int i = 0; i < (int)rect.size.h; i++) {
		unsigned char* pointer = row_pointer;
		for (int j = 0; j < (int)rect.size.w; j++) {
			*pointer++ = color.r;
			*pointer++ = color.g;
			*pointer++ = color.b;
			*pointer++ = color.a;
		}
		row_pointer += bytes_per_pixel * width;
	}
}

HtCanvas::~HtCanvas()
{
	free(src);
}