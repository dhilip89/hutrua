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
            bitmap.setPixel(i, j, color, COPY);
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

int test_draw_line_3() {
    HtCanvas canvas(500, 500);
    HtPoint p1{ 50, 50 }, p2{ 50, 150 }, p3{ 100, 250 }, p4{ 20, 450 }, d{ 25, 0 };
    HtScalar width = 0;
    for (int i = 0; i < 20; i++) {
        canvas.drawLine(p1, p2, width, HT_BLACK);
        canvas.drawLine(p3, p4, width * 2, HT_BLACK);
        p1 += d;
        p2 += d;
        p3 += d;
        p4 += d;
        width += 0.5;
    }

    HtPoint p5{ 400, 20 }, p6{ 480, 50 }, d2{ -20, 20 };
    width = 0;
    for (int i = 0; i < 23; i++) {
        canvas.drawLine(p5, p6, width, HT_RED);
        p5 += d2;
        p6 += d2;
        width += 1;
    }

    if (!save_image(canvas.getBitmap().get(), "draw_line_3.png", PNG)) {
        return 1;
    }
    return 0;
}

int test_draw_triangle() {
    HtCanvas canvas(500, 500);
    HtPoint p1{ 200, 80 }, p2{ 80, 300 }, p3{ 240, 250 }, d{ 200, 0 }, d2{ 2, 0 };
    canvas.drawTriangle(p1, p2, p3, HT_RED);
    canvas.drawHairLine(p1 + d2, p2 + d2, HT_BLACK);
    canvas.drawHairLine(p2 + d2, p3 + d2, HT_BLACK);
    canvas.drawHairLine(p3 + d2, p1 + d2, HT_BLACK);
    canvas.drawTriangle(p1 + d, p2 + d, p3 + d, HT_BLACK);

    if (!save_image(canvas.getBitmap().get(), "draw_triangle.png", PNG)) {
        return 1;
    }
    return 0;
}

int test_draw_triangle_2() {
    HtCanvas canvas(500, 500);
    HtPoint p1{ 50, 50 }, p2{ 60, 50 }, p3{ 50, 60 }, p4{ 60, 60 },
        p5{ 150, 50 }, p6{ 250, 50 }, p7{ 250, 100 }, p8{ 50, 400 },
        d{ 40, 0 }, d2{ 0, 40 };
    canvas.drawTriangle(p1, p1 - d, p1 - d2, HT_BLACK);
    canvas.drawTriangle(p2, p2 + d, p2 - d2, HT_BLACK);
    canvas.drawTriangle(p3, p3 - d, p3 + d2, HT_BLACK);
    canvas.drawTriangle(p4, p4 + d, p4 + d2, HT_BLACK);

    canvas.drawTriangle(p5, p5, p5, HT_BLACK);
    canvas.drawTriangle(p6, p6 + d2, p6 - d2, HT_BLACK);
    canvas.drawTriangle(p6, p6 + d, p6 - d, HT_BLACK);
    canvas.drawTriangle(p6, p6 + d + d2, p6 - d - d2, HT_BLACK);
    canvas.drawTriangle(p6, p6 + d - d2, p6 - d + d2, HT_BLACK);

    for (int i = 0; i < 10; i++) {
        canvas.drawTriangle(p7, p8 + i * d, p8 + (i + 0.5) * d, HT_BLACK);
    }

    if (!save_image(canvas.getBitmap().get(), "draw_triangle_2.png", PNG)) {
        return 1;
    }
    return 0;
}

int test_alpha() {
    HtCanvas canvas(500, 500);
    HtPoint p1{ 50, 50 }, p2{ 200, 50 }, d{ 20, 20 };
    HtSize size{ 50, 50 };
    HtColor c1{ 255, 0, 0, 128 }, c2{ 0, 255, 0, 128 };
    canvas.drawRect({ p1, size }, HT_BLACK);
    p1 += d;
    canvas.drawRect({ p1, size }, c1);
    p1 += d;
    canvas.drawRect({ p1, size }, c2);
    canvas.setGlobalCompositeOperation(COPY);
    canvas.drawRect({ p2, size }, HT_BLACK);
    p2 += d;
    canvas.drawRect({ p2, size }, c1);
    p2 += d;
    canvas.drawRect({ p2, size }, c2);

    if (!save_image(canvas.getBitmap().get(), "draw_alpha.png", PNG)) {
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
    if (test_draw_line_3() != 0) {
        return 1;
    }
    if (test_draw_triangle() != 0) {
        return 1;
    }
    if (test_draw_triangle_2() != 0) {
        return 1;
    }
    if (test_alpha() != 0) {
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
