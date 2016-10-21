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

	int getWidth() { return width; }
	int getHeight() { return height; }
	HtCanvasType getType() { return type; }
	std::shared_ptr<HtBitmap> getBitmap() { return bitmap; }

private:
	std::shared_ptr<HtBitmap> bitmap;
	int width;
	int height;
	HtCanvasType type;
};

#endif // HT_CANVAS_H_
