#ifndef HT_IMAGE_H_
#define HT_IMAGE_H_
#include <string>
#include "HtTypes.h"
#include "HtCanvas.h"

typedef HtCanvasType HtImageType;

enum HtImageEncodeType {
	PNG,
	BMP
};

class HtImage {
public:
	DISALLOW_COPY_AND_ASSIGN(HtImage);
	HtImage(int width, int height, HtImageType type = RGBA8888, void* data = NULL);
	~HtImage();
	bool save_image(std::string path, HtImageEncodeType);

private:
	unsigned char* src;
	int width;
	int height;
	int bytes_per_pixel;
	HtImageType type;
};

#endif // HT_IMAGE_H_
