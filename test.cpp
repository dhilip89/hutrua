#include <string>
#include <cmath>
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

    const double pi = 3.14159265358979323846;
    HtCanvas canvas2(500, 500);
    for (int i = 0; i < 360; i += 2) {
        double x = std::sin(i * pi / 180.0);
        double y = std::cos(i * pi / 180.0);
        canvas2.drawHairLine({ 250 + 200 * x * 0.25, 250 + 200 * y * 0.25 },
        { 250 + 200 * x, 250 + 200 * y }, HT_BLACK);
    }

    canvas2.drawHairLine({ 80, 80 }, { 80 + 50, 80 + 50 }, HT_RED);
    canvas2.drawHairLine({ 80, 80 }, { 80 + 50, 80 - 50 }, HT_RED);
    canvas2.drawHairLine({ 80, 80 }, { 80 - 50, 80 + 50 }, HT_RED);
    canvas2.drawHairLine({ 80, 80 }, { 80 - 50, 80 - 50 }, HT_RED);
    canvas2.drawHairLine({ 80, 80 }, { 80 + 0, 80 + 50 }, HT_RED);
    canvas2.drawHairLine({ 80, 80 }, { 80 + 50, 80 + 0 }, HT_RED);
    canvas2.drawHairLine({ 80, 80 }, { 80 + 0, 80 - 50 }, HT_RED);
    canvas2.drawHairLine({ 80, 80 }, { 80 - 50, 80 + 0 }, HT_RED);

    for (int i = 0; i < 100; i += 10) {
        canvas2.drawHairLine({ 400. + i, 400 }, { 344. + i, 444 }, HT_BLUE);
        canvas2.drawHairLine({ 344. + i + 5, 444 }, { 400. + i + 5, 400 }, HT_BLUE);
    }

    if (!save_image(canvas2.getBitmap().get(), "3.png", PNG)) {
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
