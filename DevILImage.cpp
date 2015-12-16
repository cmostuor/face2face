#include "DevILImage.h"


DevILImage::DevILImage()
{
	type = 0;
	width = 0;
	height = 0;
	format = 0;
	data = NULL;
}

DevILImage::DevILImage(ILstring path)
{
	//Load image with DevIL
	ILuint texid;
	ILboolean success;
	ilInit();
	ilGenImages(1, &texid);
	success = ilLoadImage(path);
	if(success) {
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		type = ilGetInteger(IL_IMAGE_BPP);
		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);
		format = ilGetInteger(IL_IMAGE_FORMAT);
		data = new ILubyte[width*height*4];
		memcpy(data, ilGetData(), width*height*4);
		//data = ilGetData();
		std::cout << "Image loaded successfully: " << (int)success << std::endl;
	}
	ilDeleteImages(1, &texid);
}


DevILImage::~DevILImage(void)
{
	delete &type;
	delete &width;
	delete &height;
	delete &format;
	delete data;
}
