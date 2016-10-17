#include <string>
#include "hutrua.h"
#include "HtImage.h"

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

int main() {
    hello();
	if (!test_save_png()) {
		return 1;
	}
	return 0;
}