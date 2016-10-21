#ifndef HT_IMAGE_H_
#define HT_IMAGE_H_
#include <string>
#include "HtBitmap.h"

enum HtImageEncodeType {
	PNG,
	BMP
};

bool save_image(HtBitmap* bitmap, const std::string path, HtImageEncodeType);

#endif // HT_IMAGE_H_
