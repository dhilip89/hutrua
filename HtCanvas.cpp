#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <utility>
#include <algorithm>
#include "HtCanvas.h"

HtCanvas::HtCanvas(int width, int height, HtCanvasType type)
    : bitmap(new HtBitmap(width, height)), width(width), height(height), type(type) {
    assert(width > 0 && height > 0);
    assert(type == RGBA8888);
}

void HtCanvas::clearRect(HtScalar x, HtScalar y, HtScalar w, HtScalar h) {
    drawRect({ {x, y}, {w, h} }, HT_TRANSPARENT_BLACK);
}

void HtCanvas::fillRect(HtScalar x, HtScalar y, HtScalar w, HtScalar h) {
    drawRect({ { x, y },{ w, h } }, state.fill_style);
}

void HtCanvas::strokeRect(HtScalar x, HtScalar y, HtScalar w, HtScalar h) {
    // TODO: real stroke rect
    drawRect({ { x, y },{ w, h } }, state.stroke_style);
}

void HtCanvas::drawRect(HtRect rect, HtColor color) {
    if (rect.size.h <= 0 || rect.size.w <= 0)
        return;
    int x = rect.top_left.x > 0 ? int(rect.top_left.x) : 0;
    int y = rect.top_left.y > 0 ? int(rect.top_left.y) : 0;
    int w = rect.top_left.x + rect.size.w < width ? int(rect.size.w) : width - x;
    int h = rect.top_left.y + rect.size.h < height ? int(rect.size.h) : height - y;
    bitmap->setPixels(x, y, w, h, color, state.global_composite_operation);
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

void HtCanvas::drawLine(HtPoint p1, HtPoint p2, HtScalar line_width, HtColor color) {
    if (line_width < 1) {
        drawHairLine(p1, p2, color);
        return;
    }

    HtPoint w{ p1.y - p2.y, p2.x - p1.x };
    w = 0.5 * (line_width - 1) * normal(w);
    drawTriangle(p1 + w, p1 - w, p2 + w, color);
    drawTriangle(p2 + w, p2 - w, p1 - w, color);
}

void HtCanvas::drawHairLine(int x0, int y0, int x1, int y1, HtColor color, int octant) {
    x1+=1;
    int dx = x1 - x0 + 1;
    int dy = y1 - y0 + 1;
    int D = 2 * dy - dx;
    int y = y0;
    for (int x = x0; x < x1; x++) {
        switch (octant) {
        case 0:
            bitmap->setPixel(x, y, color, state.global_composite_operation);
            break;
        case 1:
            bitmap->setPixel(y, x, color, state.global_composite_operation);
            break;
        case 2:
            bitmap->setPixel(-y, x, color, state.global_composite_operation);
            break;
        case 3:
            bitmap->setPixel(-x, y, color, state.global_composite_operation);
            break;
        case 4:
            bitmap->setPixel(-x, -y, color, state.global_composite_operation);
            break;
        case 5:
            bitmap->setPixel(-y, -x, color, state.global_composite_operation);
            break;
        case 6:
            bitmap->setPixel(y, -x, color, state.global_composite_operation);
            break;
        case 7:
            bitmap->setPixel(x, -y, color, state.global_composite_operation);
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

void HtCanvas::drawTriangle(HtPoint p1, HtPoint p2, HtPoint p3, HtColor color) {
    // top: p1, left: p2, right: p3
    if (p2.y < p1.y)
        std::swap(p1, p2);
    if (p3.y < p1.y)
        std::swap(p1, p3);
    if (p3.x < p2.x)
        std::swap(p2, p3);

    HtScalar d1, d2, x1 = p1.x, x2 = p1.x;
    d1 = p2.y - p1.y ? (p2.x - p1.x) / (p2.y - p1.y) : 0;
    d2 = p3.y - p1.y ? (p3.x - p1.x) / (p3.y - p1.y) : 0;
    for (int y = int(p1.y); y < int(std::min(p2.y, p3.y)); y++) {
        bitmap->setPixels(int(x1), int(y), int(x2) - int(x1) + 1, 1, color, state.global_composite_operation);
        x1 += d1;
        x2 += d2;
    }
    if (p2.y < p3.y) {
        d1 = p3.y - p2.y ? (p3.x - p2.x) / (p3.y - p2.y) : 0;
        x1 = p2.x;
    } else if (p2.y > p3.y) {
        d2 = p2.y - p3.y ? (p2.x - p3.x) / (p2.y - p3.y) : 0;
        x2 = p3.x;
    } else {
        x1 = p2.x;
        x2 = p3.x;
    }
    for (int y = int(std::min(p2.y, p3.y)); y <= int(std::max(p2.y, p3.y)); y++) {
        bitmap->setPixels(int(x1), int(y), int(x2) - int(x1) + 1, 1, color, state.global_composite_operation);
        x1 += d1;
        x2 += d2;
    }
}

HtScalar edgeAA(HtScalar b, HtScalar c, HtScalar r) {
    if (r >= 0 && r + b <= 0 && r + c <= 0) {
        return r * r / (2 * b * c);
    }
    else if (r <= 0 && r + b >= 0 && r + c >= 0) {
        return 1 - r * r / (2 * b * c);
    }
    else if (r + b >= 0 && r <= 0 && r + b + c <= 0) {
        return -(r + b) * (r + b) / (2 * b * c);
    }
    else if (r + b <= 0 && r >= 0 && r + b + c >= 0) {
        return 1 + (r + b) * (r + b) / (2 * b * c);
    }
    else if (r + b + c >= 0 && r + b <= 0 && r + c <= 0) {
        return (r + b + c) * (r + b + c) / (2 * b * c);
    }
    else if (r + b + c <= 0 && r + b >= 0 && r + c >= 0) {
        return 1 - (r + b + c) * (r + b + c) / (2 * b * c);
    }
    else if (r + c >= 0 && r <= 0 && r + b + c <= 0) {
        return -(r + c) * (r + c) / (2 * b * c);
    }
    else if (r + c <= 0 && r >= 0 && r + b + c >= 0) {
        return 1 + (r + c) * (r + c) / (2 * b * c);
    }
    else if (r >= 0 && r + b >= 0 && r + c <= 0) {
        return -(2 * r + b) / (2 * c);
    }
    else if (r <= 0 && r + b <= 0 && r + c >= 0) {
        return 1 + (2 * r + b) / (2 * c);
    }
    else if (r >= 0 && r + c >= 0 && r + b <= 0) {
        return -(2 * r + c) / (2 * b);
    }
    else if (r <= 0 && r + c <= 0 && r + b >= 0) {
        return 1 + (2 * r + c) / (2 * b);
    }
    else {
        assert(0);
        return 0;
    }
}

void HtCanvas::drawTriangleAA(HtPoint p0, HtPoint p1, HtPoint p2, HtColor color) {
    // 3 points in one line
    if ((p1.y - p0.y) * (p2.x - p0.x) - (p1.x - p0.x) * (p2.y - p0.y) == 0) {
        return;
    }

    // get bounding box
    int x0 = int(p0.x), y0 = int(p0.y), x1 = int(p0.x), y1 = int(p0.y);
    if (int(p1.x) < x0) x0 = int(p1.x);
    if (int(p2.x) < x0) x0 = int(p2.x);
    if (int(p1.y) < y0) y0 = int(p1.y);
    if (int(p2.y) < y0) y0 = int(p2.y);
    if (int(p1.x) > x1) x1 = int(p1.x);
    if (int(p2.x) > x1) x1 = int(p2.x);
    if (int(p1.y) > y1) y1 = int(p1.y);
    if (int(p2.y) > y1) y1 = int(p2.y);


    // base: p0, edge0 p0p1
    // point on edge: b1*(x - x0) + c1*(y - y0) = 0
    HtScalar b0 = p1.y - p0.y, c0 = p0.x - p1.x;
    if (b0 * (p2.x - p0.x) + c0 * (p2.y - p0.y) < 0) {
        b0 = -b0;
        c0 = -c0;
    }

    HtScalar b1 = p2.y - p1.y, c1 = p1.x - p2.x;
    if (b1 * (p0.x - p1.x) + c1 * (p0.y - p1.y) < 0) {
        b1 = -b1;
        c1 = -c1;
    }

    HtScalar b2 = p0.y - p2.y, c2 = p2.x - p0.x;
    if (b2 * (p1.x - p2.x) + c2 * (p1.y - p2.y) < 0) {
        b2 = -b2;
        c2 = -c2;
    }

    for (int y = y0; y <= y1; y++) {
        for (int x = x0; x <= x1; x++) {
            HtScalar r0 = b0 * (x - p0.x) + c0 * (y - p0.y),
                r1 = b1 * (x - p1.x) + c1 * (y - p1.y),
                r2 = b2 * (x - p2.x) + c2 * (y - p2.y);
            if ((r0 <= 0 && r0 + b0 <= 0 && r0 + c0 <= 0 && r0 + b0 + c0 <= 0) ||
                (r1 <= 0 && r1 + b1 <= 0 && r1 + c1 <= 0 && r1 + b1 + c1 <= 0) ||
                (r2 <= 0 && r2 + b2 <= 0 && r2 + c2 <= 0 && r2 + b2 + c2 <= 0)) {
                continue;
            }

            // pixels on edges that need anti-alising
            if (!(r0 >= 0 && r0 + b0 >= 0 && r0 + c0 >= 0 && r0 + b0 + c0 >= 0) ||
                !(r1 >= 0 && r1 + b1 >= 0 && r1 + c1 >= 0 && r1 + b1 + c1 >= 0) ||
                !(r2 >= 0 && r2 + b2 >= 0 && r2 + c2 >= 0 && r2 + b2 + c2 >= 0)) {

                bool bb0 = r0 >= 0 && r0 + b0 >= 0 && r0 + c0 >= 0 && r0 + b0 + c0 >= 0,
                    bb1 = r1 >= 0 && r1 + b1 >= 0 && r1 + c1 >= 0 && r1 + b1 + c1 >= 0,
                    bb2 = r2 >= 0 && r2 + b2 >= 0 && r2 + c2 >= 0 && r2 + b2 + c2 >= 0;

                HtColor AAColor = HT_RED;

                // one edge cross this pixel
                if (!bb0 && bb1 && bb2) { // edge0 cross this pixel
                    assert(edgeAA(b0, c0, r0) > 0);
                    AAColor = color * edgeAA(b0, c0, r0);
                } else if (bb0 && !bb1 && bb2) {
                    assert(edgeAA(b1, c1, r1) > 0);
                    AAColor = color * edgeAA(b1, c1, r1);
                } else if (bb0 && bb1 && !bb2) {
                    assert(edgeAA(b2, c2, r2) > 0);
                    AAColor = color * edgeAA(b2, c2, r2);
                }

                // two edges cross this pixel
                if (!bb0 && !bb1 && bb2) { // edge0 edge1 cross this pixel
                    if (x <= p1.x || x >= p1.x + 1 || y <= p1.y || y >= p1.y + 1) { // p1 not inside this pixel
                        HtScalar w0 = edgeAA(b0, c0, r0),
                            w1 = edgeAA(b1, c1, r1);
                        AAColor = color * (w0 + w1 - 1);
                    }
                } else if (bb0 && !bb1 && !bb2) {
                    if (x <= p2.x || x >= p2.x + 1 || y <= p2.y || y >= p2.y + 1) {
                        HtScalar w0 = edgeAA(b1, c1, r1),
                            w1 = edgeAA(b2, c2, r2);
                        AAColor = color * (w0 + w1 - 1);
                    }
                }
                else if (!bb0 && bb1 && !bb2) {
                    if (x <= p0.x || x >= p0.x + 1 || y <= p0.y || y >= p0.y + 1) {
                        HtScalar w0 = edgeAA(b0, c0, r0),
                            w1 = edgeAA(b2, c2, r2);
                        AAColor = color * (w0 + w1 - 1);
                    }
                }

                // TODO: cases of vertex isn't integer or three edges cross one pixel
                bitmap->setPixel(x, y, AAColor, state.global_composite_operation);
            } else {
                if (r0 == 0) r0 = r0 + b0 == 0 ? r0 + c0 : r0 + b0;
                if (r1 == 0) r1 = r1 + b1 == 0 ? r1 + c1 : r1 + b1;
                if (r2 == 0) r2 = r2 + b2 == 0 ? r2 + c2 : r2 + b2;

                if (r0 > 0 && r1 > 0 && r2 > 0) {
                    bitmap->setPixel(x, y, color, state.global_composite_operation);
                }
            }
        }
    }
}
