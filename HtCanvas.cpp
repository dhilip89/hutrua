#include <cassert>
#include <cstdlib>
#include <cstring>
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