#include <string>
#include "HtImage.h"
#include "HtCanvas.h"
#include "HtTypes.h"
#include "HtBitmap.h"

int test_save_image() {
	HtBitmap bitmap(256, 256);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			HtColor color{ static_cast<unsigned char>((i + j) % 256),
				static_cast<unsigned char>((256 + i - j) % 256),
				static_cast<unsigned char>((256 + j - i) % 256),
				static_cast<unsigned char>(255) };
			bitmap.setPixel(i, j, color);
		}
	}
	if (!save_image(&bitmap, "1.png", PNG)) {
		return 1;
	}
	if (!save_image(&bitmap, "1.bmp", BMP)) {
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
	if (!save_image(canvas.getBitmap().get(), "2.png", PNG)) {
		return 1;
	}
	return 0;
}

int main() {
	if (test_save_image() != 0) {
		return 1;
	}
	if (test_canvas() != 0) {
		return 1;
	}
	return 0;
}
