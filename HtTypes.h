#ifndef HT_TYPES_H_
#define HT_TYPES_H_
#include <cassert>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete

typedef double HtScalar;

typedef struct _HtPoint {
	HtScalar x;
	HtScalar y;
} HtPoint;

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

#define HT_BLACK HtColor{ 0, 0, 0, 255 }
#define HT_WHITE HtColor{ 255, 255, 255, 255 }
#define HT_GREY HtColor{ 128, 128, 128, 255 }
#define HT_RED HtColor{ 255, 0, 0, 255 }
#define HT_GREEN HtColor{ 0, 255, 0, 255 }
#define HT_BLUE HtColor{ 0, 0, 255, 255 }

#endif // HT_TYPES_H_
