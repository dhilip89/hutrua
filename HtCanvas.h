#ifndef HT_CANVAS_H_
#define HT_CANVAS_H_
#include "HtTypes.h"

#include <memory>

enum HtCanvasType {
	RGBA8888
};

class HtCanvas {
public:
	DISALLOW_COPY_AND_ASSIGN(HtCanvas);
	HtCanvas(int width, int height, HtCanvasType type = RGBA8888);
	~HtCanvas();

	void drawRect(HtRect rect, HtColor color);

	int getWidth() { return width; }
	int getHeight() { return height; }
	int getBytesPerPixel() { return bytes_per_pixel; }
	HtCanvasType getType() { return type; }
	unsigned char* getSrc() { return src; }

private:
	unsigned char* src;
	int width;
	int height;
	int bytes_per_pixel;
	HtCanvasType type;
};

#endif // HT_CANVAS_H_
