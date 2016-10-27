#include <cassert>
#include <algorithm>
#include "HtBitmap.h"

bool HtBitmap::setPixel(int x, int y, HtColor color) {
    if (x < 0 || x >= w || y < 0 || y >= h)
        return false;
    bitmap[y * w + x] = color;
    return true;
}

bool HtBitmap::setPixels(int x, int y, int ww, int hh, HtColor color) {
    if (x >= w || y >= h || ww <= 0 || h <= 0 || x + ww < 0 || y + hh < 0)
        return false;
    if (x < 0) {
        ww += x;
        x = 0;
    }
    if (y < 0) {
        hh += y;
        y = 0;
    }
    if (x + ww > w) ww = w - x;
    if (y + hh > h) hh = h - y;
    auto iter = bitmap.begin() + y * w + x;
    std::fill(iter, iter + ww, color);
    for (int i = 1; i < hh; i++) {
        iter += w;
        std::fill(iter, iter + ww, color);
    }
    return true;
}
