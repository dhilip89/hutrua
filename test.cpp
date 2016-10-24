#include <string>
#include <random>
#include <iostream>
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
    if (!save_image(&bitmap, "png_test.png", PNG)) {
        return 1;
    }
    if (!save_image(&bitmap, "bmp_test.bmp", BMP)) {
        return 1;
    }
    return 0;
}

int test_draw_rect() {
    HtCanvas canvas(100, 100);
    canvas.drawRect({ { -10, -10 },{ 20, 30 } }, HT_RED);
    canvas.drawRect({ { 50, 40 },{ 70, 80 } }, HT_GREEN);
    canvas.drawRect({ { 10, 10 },{ 50, 40 } }, HT_BLUE);
    canvas.drawRect({ { 30, 20 },{ 0, 0 } }, HT_BLUE);
    if (!save_image(canvas.getBitmap().get(), "draw_rect.png", PNG)) {
        return 1;
    }
    return 0;
}

int test_draw_line() {
    const double pi = 3.14159265358979323846;
    HtCanvas canvas(500, 500);
    for (int i = 0; i < 360; i += 2) {
        double x = std::sin(i * pi / 180.0);
        double y = std::cos(i * pi / 180.0);
        canvas.drawHairLine({ 250 + 200 * x * 0.25, 250 + 200 * y * 0.25 },
        { 250 + 200 * x, 250 + 200 * y }, HT_BLACK);
    }

    canvas.drawHairLine({ 80, 80 }, { 80 + 50, 80 + 50 }, HT_RED);
    canvas.drawHairLine({ 80, 80 }, { 80 + 50, 80 - 50 }, HT_RED);
    canvas.drawHairLine({ 80, 80 }, { 80 - 50, 80 + 50 }, HT_RED);
    canvas.drawHairLine({ 80, 80 }, { 80 - 50, 80 - 50 }, HT_RED);
    canvas.drawHairLine({ 80, 80 }, { 80 + 0, 80 + 50 }, HT_RED);
    canvas.drawHairLine({ 80, 80 }, { 80 + 50, 80 + 0 }, HT_RED);
    canvas.drawHairLine({ 80, 80 }, { 80 + 0, 80 - 50 }, HT_RED);
    canvas.drawHairLine({ 80, 80 }, { 80 - 50, 80 + 0 }, HT_RED);

    for (int i = 0; i < 100; i += 10) {
        canvas.drawHairLine({ 400. + i, 400 }, { 344. + i, 444 }, HT_BLUE);
        canvas.drawHairLine({ 344. + i + 5, 444 }, { 400. + i + 5, 400 }, HT_BLUE);
    }

    if (!save_image(canvas.getBitmap().get(), "draw_line.png", PNG)) {
        return 1;
    }
    return 0;
}

int test_draw_line_2() {
    HtCanvas canvas(500, 500);
    std::mt19937 gen;
    std::uniform_int_distribution<> dis_color(0, 255);
    std::uniform_int_distribution<> dis_pos(-600, 600);
    for (int i = 0; i < 1000; i++) {
        canvas.drawHairLine({ static_cast<HtScalar>(dis_pos(gen)), static_cast<HtScalar>(dis_pos(gen)) },
            { static_cast<HtScalar>(dis_pos(gen)), static_cast<HtScalar>(dis_pos(gen)) },
            { static_cast<unsigned char>(dis_color(gen)), static_cast<unsigned char>(dis_color(gen)), 
            static_cast<unsigned char>(dis_color(gen)), 255});
    }

    if (!save_image(canvas.getBitmap().get(), "draw_line_2.png", PNG)) {
        return 1;
    }
    return 0;
}

int test_canvas() {
    if (test_draw_rect() != 0) {
        return 1;
    }
    if (test_draw_line() != 0) {
        return 1;
    }
    if (test_draw_line_2() != 0) {
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
