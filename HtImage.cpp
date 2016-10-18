#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstdint>
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

bool HtImage::save_image(std::string path, HtImageEncodeType encode_type)
{
	if (type != RGBA8888) {
		return false;
	}

	if (encode_type == PNG) {
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
		return true;
	}
	else if (encode_type = BMP) {
		FILE *fp;
		fp = fopen(path.c_str(), "wb");
		if (fp == NULL) {
			return false;
		}
		# pragma pack (1)
		struct BMP_header {
			char id[2] = { 'B', 'M' };
			uint32_t size;
			uint32_t unused = 0;
			uint32_t offset = 14 + 108;
		} bmp_header;
		struct DIB_header {
			uint32_t DIB_header_size = 108;
			int32_t width;
			int32_t height;
			uint16_t plane = 1;
			uint16_t bits_per_pixel = 32;
			uint32_t compression = 3;
			uint32_t bitmap_size;
			uint32_t res_h = 2835;
			uint32_t res_v = 2835;
			uint32_t colors = 0;
			uint32_t important_colors = 0;
			uint32_t bitmask[4] = {0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000};
			uint32_t color_space = 0x206e6957;
			uint32_t unused[12];
		} BITMAPV4HEADER;
		# pragma pack ()
		assert(sizeof(BMP_header) == 14);
		assert(sizeof(DIB_header) == 108);
		BITMAPV4HEADER.width = width;
		BITMAPV4HEADER.height = height;
		BITMAPV4HEADER.bitmap_size = width * height * bytes_per_pixel;
		bmp_header.size = 14 + 108 + BITMAPV4HEADER.bitmap_size;
		fwrite(&bmp_header, sizeof(bmp_header), 1, fp);
		fwrite(&BITMAPV4HEADER, sizeof(BITMAPV4HEADER), 1, fp);

		// bmp data starts with the lower left hand corner of the image
		unsigned char* row_pointer = src + BITMAPV4HEADER.bitmap_size;
		for (int k = 0; k < height; k++) {
			row_pointer -= width * bytes_per_pixel;
			fwrite(row_pointer, width * bytes_per_pixel, 1, fp);
		}
		fclose(fp);
		return true;
	} else {
		return false;
	}
}
