#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>

#include "HtImage.h"
#include "png.h"

HtImage::HtImage(int width, int height, HtImageType type, void* data)
{
	assert(width > 0 && height > 0);

	HtImage::width = width;
	HtImage::height = height;
	HtImage::type = type;

	switch (type) {
	case RGBA8888:
		bytes_per_pixel = 4;
		break;
	default:
		exit(1);
	}

	int size = width * height * bytes_per_pixel * sizeof(unsigned char);

	src = (unsigned char*) malloc(size);
	if (!src) {
		exit(1);
	}

	if (data) {
		memcpy(src, data, size);
	}
	else {
		memset(src, 0, size);
	}
}

HtImage::~HtImage()
{
	free(src);
}

bool HtImage::save_image(std::string path, HtImageEncodeType type)
{
	if (type != PNG) {
		return false;
	}

	FILE *fp;
	fp = fopen(path.c_str(), "wb");
	if (fp == NULL) {
		return false;
	}
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fclose(fp);
		return false;
	}
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_write_struct(&png_ptr, NULL);
		return false;
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return false;
	}
	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	png_bytep row_pointer = src;
	for (int k = 0; k < height; k++) {
		png_write_rows(png_ptr, &row_pointer, 1);
		row_pointer += width * bytes_per_pixel;
	}
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	return 0;
}