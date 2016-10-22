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
    if (x < 0 || y < 0 || ww <= 0 || hh <= 0 || x + ww > w || y + hh > h)
        return false;
    auto iter = bitmap.begin() + y * w + x;
    std::fill(iter, iter + ww, color);
    for (int i = 1; i < hh; i++) {
        iter += w;
        std::fill(iter, iter + ww, color);
    }
    return true;
}
