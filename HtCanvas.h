#ifndef HT_CANVAS_H_
#define HT_CANVAS_H_
#include "HtTypes.h"
#include "HtBitmap.h"
#include <memory>

enum HtCanvasType {
    RGBA8888
};

class HtCanvas {
public:
    HtCanvas(int width, int height, HtCanvasType type = RGBA8888);

    void drawRect(HtRect rect, HtColor color);
    void drawHairLine(HtPoint p1, HtPoint p2, HtColor color);
    void drawLine(HtPoint p1, HtPoint p2, HtScalar width, HtColor color);
    void drawTriangle(HtPoint p1, HtPoint p2, HtPoint p3, HtColor color);

    int getWidth() { return width; }
    int getHeight() { return height; }
    HtCanvasType getType() { return type; }
    std::shared_ptr<HtBitmap> getBitmap() { return bitmap; }

private:
    void drawHairLine(int x0, int y0, int x1, int y1, HtColor color, int octant);

    std::shared_ptr<HtBitmap> bitmap;
    int width;
    int height;
    HtCanvasType type;
};

#endif // HT_CANVAS_H_
