#include <string>
#include "hutrua.h"
#include "HtImage.h"
#include "HtCanvas.h"
#include "HtTypes.h"

int test_save_png() {
	unsigned char bitmap[256 * 256 * 4];
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			bitmap[i * 256 * 4 + j * 4] = (i + j) % 256;
			bitmap[i * 256 * 4 + j * 4 + 1] = (256 + i - j) % 256;
			bitmap[i * 256 * 4 + j * 4 + 2] = (256 + j - i) % 256;
			bitmap[i * 256 * 4 + j * 4 + 3] = 255;
		}
	}
	HtImage image(256, 256, RGBA8888, bitmap);
	if (!image.save_image("1.png", PNG)) {
		return 1;
	}
	return 0;
}

int test_save_bmp() {
	unsigned char bitmap[256 * 256 * 4];
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			bitmap[i * 256 * 4 + j * 4] = (i + j) % 256;
			bitmap[i * 256 * 4 + j * 4 + 1] = (256 + i - j) % 256;
			bitmap[i * 256 * 4 + j * 4 + 2] = (256 + j - i) % 256;
			bitmap[i * 256 * 4 + j * 4 + 3] = 255;
		}
	}
	HtImage image(256, 256, RGBA8888, bitmap);
	if (!image.save_image("1.bmp", BMP)) {
		return 1;
	}
	return 0;
}

int test_canvas() {
	HtCanvas canvas(100, 100);
	canvas.drawRect({ { -10, -10 }, { 20, 30 } }, HT_RED);
	canvas.drawRect({ { 50, 40 }, { 70, 80 } }, HT_GREEN);
	canvas.drawRect({ { 10, 10 },{ 50, 40 } }, HT_BLUE);
	canvas.drawRect({ { 30, 20 }, { 0, 0 } }, HT_BLUE);
	HtImage image(canvas.getWidth(), canvas.getHeight(), canvas.getType(), canvas.getSrc());
	image.save_image("2.png", PNG);
	return 0;
}

int main() {
    hello();
	if (test_save_png() != 0) {
		return 1;
	}
	if (test_save_bmp() != 0) {
		return 1;
	}
	if (test_canvas() != 0) {
		return 1;
	}
	return 0;
}
