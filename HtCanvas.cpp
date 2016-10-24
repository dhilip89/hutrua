#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "HtCanvas.h"

HtCanvas::HtCanvas(int width, int height, HtCanvasType type)
    : width(width), height(height), type(type) {
    assert(width > 0 && height > 0);
    assert(type == RGBA8888);
    bitmap.reset(new HtBitmap(width, height));
}

void HtCanvas::drawRect(HtRect rect, HtColor color) {
    if (rect.size.h <= 0 || rect.size.w <= 0)
        return;
    int x = rect.top_left.x > 0 ? int(rect.top_left.x) : 0;
    int y = rect.top_left.y > 0 ? int(rect.top_left.y) : 0;
    int w = rect.top_left.x + rect.size.w < width ? int(rect.size.w) : width - x;
    int h = rect.top_left.y + rect.size.h < height ? int(rect.size.h) : height - y;
    bitmap->setPixels(x, y, w, h, color);
}

void HtCanvas::drawHairLine(HtPoint p1, HtPoint p2, HtColor color) {
    if (p1.y <= p2.y) {
        if (p1.x <= p2.x) {
            if (p2.y - p1.y < p2.x - p1.x) {
                drawHairLine(int(p1.x), int(p1.y), int(p2.x), int(p2.y), color, 0);
            } else {
                drawHairLine(int(p1.y), int(p1.x), int(p2.y), int(p2.x), color, 1);
            }
        } else {
            if (p2.y - p1.y > p1.x - p2.x) {
                drawHairLine(int(p1.y), int(-p1.x), int(p2.y), int(-p2.x), color, 2);
            } else {
                drawHairLine(int(-p1.x), int(p1.y), int(-p2.x), int(p2.y), color, 3);
            }
        }
    } else {
        if (p1.x > p2.x) {
            if (p2.y - p1.y > p2.x - p1.x) {
                drawHairLine(int(-p1.x), int(-p1.y), int(-p2.x), int(-p2.y), color, 4);
            } else {
                drawHairLine(int(-p1.y), int(-p1.x), int(-p2.y), int(-p2.x), color, 5);
            }
        } else {
            if (p1.y - p2.y > p2.x - p1.x) {
                drawHairLine(int(-p1.y), int(p1.x), int(-p2.y), int(p2.x), color, 6);
            } else {
                drawHairLine(int(p1.x), int(-p1.y), int(p2.x), int(-p2.y), color, 7);
            }
        }
    }
}

void HtCanvas::drawHairLine(int x0, int y0, int x1, int y1, HtColor color, int octant)
{
    x1+=1;
    int dx = x1 - x0 + 1;
    int dy = y1 - y0 + 1;
    int D = 2 * dy - dx;
    int y = y0;
    for (int x = x0; x < x1; x++) {
        switch (octant) {
        case 0:
            bitmap->setPixel(x, y, color);
            break;
        case 1:
            bitmap->setPixel(y, x, color);
            break;
        case 2:
            bitmap->setPixel(-y, x, color);
            break;
        case 3:
            bitmap->setPixel(-x, y, color);
            break;
        case 4:
            bitmap->setPixel(-x, -y, color);
            break;
        case 5:
            bitmap->setPixel(-y, -x, color);
            break;
        case 6:
            bitmap->setPixel(y, -x, color);
            break;
        case 7:
            bitmap->setPixel(x, -y, color);
            break;
        default:
            break;
        }
        if (D > 0) {
            y++;
            D -= dx;
        }
        D += dy;
    }
}
