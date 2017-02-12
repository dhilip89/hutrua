#ifndef HT_TYPES_H_
#define HT_TYPES_H_
#include <cassert>
#include <cmath>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete;    \
    void operator=(const TypeName&) = delete

typedef double HtScalar;

typedef struct _HtPoint {
    HtScalar x;
    HtScalar y;
} HtPoint;

inline const HtPoint operator+(const HtPoint& a, const HtPoint& b) {
    return HtPoint{ a.x + b.x, a.y + b.y };
}

inline const HtPoint operator-(const HtPoint& a, const HtPoint& b) {
    return HtPoint{ a.x - b.x, a.y - b.y };
}

inline HtPoint& operator+=(HtPoint& a, const HtPoint& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

inline HtPoint& operator-=(HtPoint& a, const HtPoint& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

inline const HtPoint operator* (const HtScalar &a, const HtPoint &b) {
    return HtPoint{ a * b.x, a * b.y };
}

inline const HtPoint normal(const HtPoint& p) {
    HtScalar w = 1 / std::sqrt(p.x * p.x + p.y * p.y);
    return w * p;
}

typedef struct _HtSize {
    HtScalar w;
    HtScalar h;
} HtSize;

typedef struct _HtRect {
    HtPoint top_left;
    HtSize size;
} HtRect;

typedef struct _HtColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} HtColor;

inline const HtColor operator* (const HtColor& color, const HtScalar &w) {
    return HtColor{
        color.r,
        color.g,
        color.b,
        (unsigned char)(HtScalar(color.a) * w)
    };
}

#define HT_BLACK             HtColor{   0,   0,   0, 255 }
#define HT_TRANSPARENT_BLACK HtColor{   0,   0,   0,   0 }
#define HT_WHITE             HtColor{ 255, 255, 255, 255 }
#define HT_GREY              HtColor{ 128, 128, 128, 255 }
#define HT_RED               HtColor{ 255,   0,   0, 255 }
#define HT_GREEN             HtColor{   0, 255,   0, 255 }
#define HT_BLUE              HtColor{   0,   0, 255, 255 }

enum HtCompositeOperation {
    SOURCE_ATOP,
    SOURCE_IN,
    SOURCE_OUT,
    SOURCE_OVER,
    DESTINATION_ATOP,
    DESTINATION_IN,
    DESTINATION_OUT,
    DESTINATION_OVER,
    LIGHTER,
    COPY,
    XOR
};

#endif // HT_TYPES_H_
