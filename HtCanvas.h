#ifndef HT_CANVAS_H_
#define HT_CANVAS_H_
#include "HtTypes.h"
#include "HtBitmap.h"
#include <memory>
#include <stack>

enum HtCanvasType {
    RGBA8888
};

enum HtLineCapType {
    BUTT,
    ROUND,
    SQUARE
};

struct HtCanvasDrawingState {
    HtColor stroke_style = HT_BLACK;
    HtColor fill_style = HT_BLACK;
    HtScalar global_alpha = 1.0;
    HtScalar line_width = 1.0;
    HtLineCapType line_cap = BUTT;
    HtCompositeOperation global_composite_operation = SOURCE_OVER;
};

class HtCanvas {
public:
    HtCanvas(int width, int height, HtCanvasType type = RGBA8888);

    // Canvas drawing APIs
    void clearRect(HtScalar x, HtScalar y, HtScalar w, HtScalar h);

    void fillRect(HtScalar x, HtScalar y, HtScalar w, HtScalar h);

    void strokeRect(HtScalar x, HtScalar y, HtScalar w, HtScalar h);

    // Save/restore canvas state
    void save() { state_stack.push(state); }

    void restore() {
        if(state_stack.empty()) return;
        state = state_stack.top();
        state_stack.pop();
    }


    void drawRect(HtRect rect, HtColor color);

    void drawHairLine(HtPoint p1, HtPoint p2, HtColor color);

    void drawHairLineAA(HtPoint p1, HtPoint p2, HtColor color);

    void drawLine(HtPoint p1, HtPoint p2, HtScalar width, HtColor color);

    void drawLineAA(HtPoint p1, HtPoint p2, HtScalar width, HtColor color);

    void drawTriangle(HtPoint p1, HtPoint p2, HtPoint p3, HtColor color);

    void drawTriangleAA(HtPoint p0, HtPoint p1, HtPoint p2, HtColor color);


    // Get/set canvas properties.
    int getWidth() const { return width; }

    int getHeight() const { return height; }

    HtColor getStrokeStyle() const { return state.stroke_style; }

    void setStrokeStyle(HtColor color) { state.stroke_style = color; }

    HtColor getFillStyle() const { return state.fill_style; }

    void setFillStyle(HtColor color) { state.fill_style = color; }

    HtScalar getGlobalAlpha() const { return state.global_alpha; }

    void setGlobalAlpha(HtScalar alpha) { if (alpha >= 0 && alpha <= 1.0) state.global_alpha = alpha; }

    HtScalar getLineWidth() const { return state.line_width; }

    void setLineWidth(HtScalar w) { state.line_width = w; }

    HtLineCapType getLineCap() const { return state.line_cap; }

    void setLineCap(HtLineCapType line_cap) { state.line_cap = line_cap; }

    HtCompositeOperation getGlobalCompositeOperation() const { return state.global_composite_operation; }

    void setGlobalCompositeOperation(HtCompositeOperation operation) { state.global_composite_operation = operation; }

    HtCanvasType getType() const { return type; }

    std::shared_ptr<HtBitmap> getBitmap() { return bitmap; }

private:
    void drawHairLine(int x0, int y0, int x1, int y1, HtColor color, int octant);

    std::shared_ptr<HtBitmap> bitmap;
    int width;
    int height;
    HtCanvasType type;
    HtCanvasDrawingState state;
    std::stack<HtCanvasDrawingState> state_stack;
};

#endif // HT_CANVAS_H_
