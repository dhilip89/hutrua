#include <cassert>
#include <algorithm>
#include "HtBitmap.h"

bool HtBitmap::setPixel(int x, int y, HtColor color, HtCompositeOperation operation) {
    if (x < 0 || x >= w || y < 0 || y >= h)
        return false;
    if (color.a == 255 || operation == COPY) {
        bitmap[y * w + x] = color;
    } else if (operation == SOURCE_OVER) {
        HtColor original = bitmap[y * w + x];
        HtScalar aa = color.a / 255.0;
        HtScalar ab = original.a / 255.0 * (1 - aa);
        HtScalar a = aa + ab;
        HtScalar r = (color.r * aa + original.r * ab) / a;
        HtScalar g = (color.g * aa + original.g * ab) / a;
        HtScalar b = (color.b * aa + original.b * ab) / a;
        bitmap[y * w + x] = HtColor{ static_cast<unsigned char>(r), static_cast<unsigned char>(g),
            static_cast<unsigned char>(b), static_cast<unsigned char>(a) };
    } else {
        return false;
    }
    return true;
}

bool HtBitmap::setPixels(int x, int y, int ww, int hh, HtColor color, HtCompositeOperation operation) {
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
    auto iter = bitmap.begin() + y * w;
    for (int i = 0; i < hh; i++) {
        if (color.a == 255 || operation == COPY) {
            std::fill(iter + x, iter + x + ww, color);
        } else if (operation == SOURCE_OVER) {
            std::for_each(iter + x, iter + x + ww, [&color](HtColor& original) {
                HtScalar aa = color.a / 255.0;
                HtScalar ab = original.a / 255.0 * (1 - aa);
                HtScalar a = aa + ab;
                HtScalar r = (color.r * aa + original.r * ab) / a;
                HtScalar g = (color.g * aa + original.g * ab) / a;
                HtScalar b = (color.b * aa + original.b * ab) / a;
                original.r = static_cast<unsigned char>(r);
                original.g = static_cast<unsigned char>(g);
                original.b = static_cast<unsigned char>(b);
                original.a = static_cast<unsigned char>(a * 255);
            });
        } else {
            return false;
        }
        iter += w;
    }
    return true;
}
