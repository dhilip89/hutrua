#ifndef HTIMAGE_H_
#define HTIMAGE_H_
#include <string>

enum HtImageType {
	RGBA8888
};

enum HtImageEncodeType {
	PNG
};

class HtImage {
public:
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

#endif // HTIMAGE_H_