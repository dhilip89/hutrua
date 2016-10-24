#ifndef HT_BITMAP_H_
#define HT_BITMAP_H_
#include <vector>
#include "HtTypes.h"

class HtBitmap {
public:
    HtBitmap(int w, int h, HtColor color = HT_WHITE) : w(w), h(h), bitmap(w * h, color) {};
    int getW() { return w; }
    int getH() { return h; }
    HtColor* getRawData() { return bitmap.data(); }
    bool setPixel(int x, int y, HtColor color);
    bool setPixels(int x, int y, int w, int h, HtColor);

private:
    int w;
    int h;
    std::vector<HtColor> bitmap;
};

#endif // HT_BITMAP_H_
